package sockets03.tcp;

import java.io.IOException;
import java.net.*;

public class Server extends Thread{
    int port;
    ServerSocket server;
    Interaction interaction;
    boolean running;
    public Server(int port, Interaction interaction) throws IOException {
        this.port = port;
        this.server = new ServerSocket(port);
        this.interaction = interaction;
        this.running = false;
    }

    public void connect() throws IOException {
        Socket socket = server.accept();
        new Thread(() -> {
            interaction.interact(socket);
            try {socket.close();} 
            catch (IOException e) {e.printStackTrace();}
        }).start();
    }

    @Override
    public void run() {
        running = true;
        while(running) {          
            try {connect();} 
            catch (IOException ex) {ex.printStackTrace(); running = false;}
        }
    }

    public void stopRunning() {running = false;}

    @Override
    public String toString() {
        return "Server: " + server.getInetAddress() + " listening in " + server.getLocalPort();
    }

    public ServerSocket getServerSocket(int port) {return server;}
}