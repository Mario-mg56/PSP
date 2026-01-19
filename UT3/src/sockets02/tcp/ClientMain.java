package sockets02.tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class ClientMain {
    public final static String HOST = "192.168.1.212";
    public final static int PORT = 5555, ELEMENTS = 10, CLIENTS = 3;
    public static void main(String[] args) {
        for (int i = 0; i < CLIENTS; i++) {
            int ti = i;
            new Client(HOST, PORT, (socket) -> interact(socket, ELEMENTS, ti)).start();
        }
    }

    private static void interact(Socket socket, int elements, int threadId) {
        try {
            DataInputStream input = new DataInputStream(socket.getInputStream());
            DataOutputStream output = new DataOutputStream(socket.getOutputStream());

            System.out.println(threadId + " connected with " + socket.getInetAddress().getHostAddress());
            for (int i = 0; i < elements; i++) output.writeInt((int) (9*Math.random() + 1)); //Random [1, 10]
            output.writeInt(-1);
            System.out.println("Server output: " + input.readInt());
            System.out.println(socket.getInetAddress().getHostAddress() + " disconnected");

            input.close();
            output.close();
        }
        catch (IOException ex) {ex.printStackTrace();}
    }
}


