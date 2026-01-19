package sockets01.udp;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;

public class Server {
    public static void main(String[] args) {
        int port = 5555;
        try {
            DatagramSocket socket = new DatagramSocket(port);

            byte[] numBytes = new byte[4];
            DatagramPacket numPacket = new DatagramPacket(numBytes, numBytes.length);

            System.out.println("Esperando a cliente 1...");
            socket.receive(numPacket);
            int num = ByteBuffer.wrap(numPacket.getData()).getInt();
            System.out.println(num + " recibido de cliente 1");

            //El servidor recibe un paquete vacio de cliente 2 para tener su información
            DatagramPacket numPacket2 = new DatagramPacket(numBytes, numBytes.length);;
            System.out.println("Esperando a cliente 2...");
            socket.receive(numPacket2);
            
            ByteBuffer bb = ByteBuffer.allocate(4); //Un int son 4 bytes
            bb.putInt(num);
            numBytes = bb.array();
            numPacket2 = new DatagramPacket(numBytes, numBytes.length, numPacket2.getAddress(), numPacket2.getPort());
            socket.send(numPacket2);
            System.out.println(num + " Enviado a cliente 2, esperando respuesta...");
            
            numPacket2 = new DatagramPacket(numBytes, numBytes.length);;
            socket.receive(numPacket2);
            num = ByteBuffer.wrap(numPacket2.getData()).getInt();
            System.out.println(num + " recibido de cliente 2");

            bb.clear();
            bb.putInt(num);
            numBytes = bb.array();
            numPacket = new DatagramPacket(numBytes, numBytes.length, numPacket.getAddress(), numPacket.getPort());
            socket.send(numPacket);
            System.out.println(num + " Enviado a cliente 1");

            socket.close();
        }
        catch (IOException excepcion) {excepcion.printStackTrace();}
  }
}