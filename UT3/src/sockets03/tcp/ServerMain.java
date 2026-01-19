package sockets03.tcp;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class ServerMain {
    public final static int PORT = 5555;
    public static void main(String[] args) throws IOException {
        new Server(PORT, (socket) -> interact(socket)).start();
    }

    private static void interact(Socket socket) {
        try {
            ObjectInputStream objectInput = new ObjectInputStream(socket.getInputStream());
            Bill bill = (Bill) objectInput.readObject();
            bill.calculate();

            ObjectOutputStream objectOutput = new ObjectOutputStream(socket.getOutputStream());
            objectOutput.writeObject(bill);
            System.out.println("Sended calculated bill with " + bill.ivaAmount + "€ iva");
            
            objectOutput.close();
            objectInput.close();
        }
        catch (IOException | ClassNotFoundException ex) {ex.printStackTrace();}
    }
}


