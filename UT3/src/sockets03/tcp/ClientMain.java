package sockets03.tcp;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.time.LocalDate;

public class ClientMain {
    public final static String HOST = "192.168.1.212";
    public final static int PORT = 5555, CLIENTS = 3;
    public static void main(String[] args) {
        for (int i = 0; i < CLIENTS; i++) {
            int ti = i;
            new Client(HOST, PORT, (socket) -> interact(socket, ti)).start();
        }
    }

    private static void interact(Socket socket, int threadId) {
        try {
            ObjectOutputStream objectOutput = new ObjectOutputStream(socket.getOutputStream());
            Bill bill =
                new Bill("Fact-1234", LocalDate.now(), (float) (300f*Math.random()), Bill.IVA.ESP);
            objectOutput.writeObject(bill);
            System.out.println("Sended " + bill.importe + "€ bill");

            ObjectInputStream objectInput = new ObjectInputStream(socket.getInputStream());
            bill = (Bill) objectInput.readObject();
            System.out.println("Recieved " + bill.importe + "€ bill with " + bill.ivaAmount + "€ iva");
            
            objectOutput.close();
            objectInput.close();
        }
        catch (IOException | ClassNotFoundException ex) {ex.printStackTrace();}
    }
}


