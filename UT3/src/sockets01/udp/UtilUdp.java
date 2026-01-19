package sockets01.udp;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.nio.ByteBuffer;

public class UtilUdp {
    public static DatagramPacket makeStringPack(String str, InetAddress address, int port) {
        byte[] bytes = str.getBytes();
        return new DatagramPacket(bytes, bytes.length, address, port);
    }

    public static DatagramPacket makeIntPack(int num, InetAddress address, int port) {
        ByteBuffer bb = ByteBuffer.allocate(4); //Un int son 4 bytes
        bb.putInt(num);
        byte[] bytes = bb.array();
        return new DatagramPacket(bytes, bytes.length, address, port);
    }

    public static DatagramPacket makeFloatPack(float num, InetAddress address, int port) {
        ByteBuffer bb = ByteBuffer.allocate(4); //Un float son 4 bytes
        bb.putFloat(num);
        byte[] bytes = bb.array();
        return new DatagramPacket(bytes, bytes.length, address, port);
    }
}
