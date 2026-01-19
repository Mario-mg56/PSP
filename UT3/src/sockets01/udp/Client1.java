package sockets01.udp;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Scanner;

public class Client1 {
    public static void main(String[] args) {
        String host = "192.168.1.212";
        int port = 5555;
        try {
            Scanner sc = new Scanner(System.in);
            System.out.println("Introduzca un número natural:");
            int num = sc.nextInt();
            if (num<0) {
                System.out.println("Introduce un número mayor que 0");
                sc.close();
                return;
            }
            DatagramSocket socket = new DatagramSocket();
            InetAddress ip = InetAddress.getByName(host);

            ByteBuffer bb = ByteBuffer.allocate(4); //Un int son 4 bytes
            bb.putInt(num);
            byte[] numBytes = bb.array();

            DatagramPacket numPacket = new DatagramPacket(numBytes, numBytes.length, ip, port);
            socket.send(numPacket); 
            System.out.println(num + " Enviado al server, esperando respuesta...");

            numPacket = new DatagramPacket(numBytes, numBytes.length);
            socket.receive(numPacket);
            num = ByteBuffer.wrap(numPacket.getData()).getInt();   
            System.out.println(num + " recibido del server");

            sc.close();
            socket.close(); 
        } 
        catch (IOException excepcion) {excepcion.printStackTrace();}
    }
}