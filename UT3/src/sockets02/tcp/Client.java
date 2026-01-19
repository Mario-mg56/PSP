package sockets02.tcp;

import java.io.IOException;
import java.net.*;

public class Client extends Thread {
    InetAddress ip;
    String host;
    int port;
    Socket socket;
    Interaction interaction;
    
    public Client(String host, int port, Interaction interaction) {
        this.host = host;
        this.port = port;
        this.interaction = interaction;
    }

    public void connect() throws IOException {
        socket = new Socket(host, port);
        ip = socket.getInetAddress();
        interaction.interact(socket);
        socket.close();
    }

    @Override
	public void run() {
		try {connect();} 
        catch (IOException ex) {ex.printStackTrace();}
	}
    
    @Override
    public String toString() {
        return "Client: " + socket.getLocalAddress() + " connected with " + ip.getHostAddress();
    }
}