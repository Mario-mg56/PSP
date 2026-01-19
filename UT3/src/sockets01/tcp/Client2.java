package sockets01.tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;

public class Client2 {
    public static void main(String[] args) {
        String host = "192.168.204.212";
        int port = 5555;
        try {
            System.out.println("Esperando al server...");
            Socket socket = new Socket(host, port);
            
            DataInputStream serverInput = new DataInputStream(socket.getInputStream());
            DataOutputStream serverOutput = new DataOutputStream(socket.getOutputStream());

            int num = serverInput.readInt();
            System.out.println(num + " recibido del server");
            
            for (int i = num-1; i > 1; i--) num *= i; //Factorial de num

            serverOutput.writeInt(num);
            System.out.println(num + " Enviado al server");
            
            socket.close(); 
            serverInput.close();
            serverOutput.close();
        } 
        catch (IOException excepcion) {excepcion.printStackTrace();}
    }
}