package sockets02.tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class ServerMain {
    public final static int PORT = 5555;
    public static void main(String[] args) throws IOException {
        new Server(PORT, (socket) -> interact(socket)).start();
    }

    private static void interact(Socket socket) {
        try {
            DataInputStream input = new DataInputStream(socket.getInputStream());
            DataOutputStream output = new DataOutputStream(socket.getOutputStream());
            System.out.println("Connected with" + socket.getInetAddress());
            
            int num = -2, sum = 0;
            while(num != -1) {
                num = input.readInt();
                if (num != -1) {
                    sum += num;
                    System.out.println(num  + " recibido de " + socket.getInetAddress());
                }
            }
            output.writeInt(sum);

            input.close();
            output.close();
        }
        catch (IOException ex) {ex.printStackTrace();}
    }
}


