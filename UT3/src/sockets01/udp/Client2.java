package sockets01.udp;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;

public class Client2 {
    public static void main(String[] args) {
        String host = "192.168.1.212";
        int port = 5555;
        try {
            DatagramSocket socket = new DatagramSocket();
            InetAddress ip = InetAddress.getByName(host);
        
            byte[] numBytes = new byte[4]; 

            DatagramPacket numPacket = new DatagramPacket(numBytes, numBytes.length, ip, port);
            socket.send(numPacket); //Envíamos paquete vacio para que el servidor nos reconozca
            System.out.println("Esperando al server...");
            
            numPacket = new DatagramPacket(numBytes, numBytes.length);
            socket.receive(numPacket);
            int num = ByteBuffer.wrap(numPacket.getData()).getInt();   
            System.out.println(num + " recibido del server");
            
            for (int i = num-1; i > 1; i--) num *= i; //Factorial de num
            
            ByteBuffer bb = ByteBuffer.allocate(4); //Un int son 4 bytes
            bb.putInt(num);
            numBytes = bb.array();
            numPacket = new DatagramPacket(numBytes, numBytes.length, ip, port);
            socket.send(numPacket);
            System.out.println(num + " Enviado al server");
            
            socket.close();
        } 
        catch (IOException excepcion) {excepcion.printStackTrace();}
    }
}