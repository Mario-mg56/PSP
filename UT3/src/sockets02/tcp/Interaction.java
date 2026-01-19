package sockets02.tcp;

import java.net.Socket;

@FunctionalInterface
public interface Interaction {
    void interact(Socket socket);
}
