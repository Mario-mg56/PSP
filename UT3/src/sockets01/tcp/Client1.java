package sockets01.tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class Client1 {
    public static void main(String[] args) {
        String host = "192.168.204.212";
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

            System.out.println("Esperando al server...");
            Socket socket = new Socket(host, port);
            
            DataInputStream serverInput = new DataInputStream(socket.getInputStream());
            DataOutputStream serverOutput = new DataOutputStream(socket.getOutputStream());

            serverOutput.writeInt(num);
            System.out.println(num + " Enviado al server, esperando respuesta...");
            num = serverInput.readInt();
            System.out.println(num + " recibido del server");
            serverOutput.writeBoolean(true);
            
            sc.close();
            socket.close(); 
            serverInput.close();
            serverOutput.close();

        } 
        catch (IOException excepcion) {excepcion.printStackTrace();}
    }
}