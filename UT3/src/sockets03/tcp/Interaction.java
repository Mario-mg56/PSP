package sockets03.tcp;

import java.net.Socket;

@FunctionalInterface
public interface Interaction {
    void interact(Socket socket);
}
