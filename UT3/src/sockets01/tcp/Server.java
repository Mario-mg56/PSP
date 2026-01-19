package sockets01.tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.*;

public class Server {
    public static void main(String[] args) {
        int port = 5555;
        try {
            ServerSocket server = new ServerSocket(port); //Se crea socket de servidor asociado al puerto

            System.out.println("Esperando a cliente 1...");
            Socket client1 = server.accept();
            System.out.println(client1.getInetAddress() + " conectado"); //InetAddress es la ip
            DataInputStream cl1Input = new DataInputStream(client1.getInputStream());
            DataOutputStream cl1Output = new DataOutputStream(client1.getOutputStream());
            
            int num = cl1Input.readInt();
            System.out.println(num + " recibido de cliente 1");

            System.out.println("Esperando a cliente 2...");
            Socket client2 = server.accept();
            System.out.println(client1.getInetAddress() + " conectado");
            DataInputStream cl2Input = new DataInputStream(client2.getInputStream());
            DataOutputStream cl2Output = new DataOutputStream(client2.getOutputStream());

            cl2Output.writeInt(num);
            System.out.println(num + " Enviado a cliente 2, esperando respuesta...");
            num = cl2Input.readInt();
            System.out.println(num + " recibido de cliente 2");

            cl1Output.writeInt(num);
            System.out.println(num + " Enviado a cliente 1");
            
            cl1Input.readBoolean(); //Cuando el cliente reciba el anterior mensaje, cerramos la conexión
            System.out.println("Conexión completada con éxito");

            server.close();
            client1.close();
            client2.close();
            cl1Input.close();
            cl1Output.close();
            cl2Input.close();
            cl2Output.close();
        } 
        catch (IOException excepcion) {excepcion.printStackTrace();}
  }
}