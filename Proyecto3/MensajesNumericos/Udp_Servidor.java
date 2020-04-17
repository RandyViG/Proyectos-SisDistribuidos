import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;  //Para manejo de ByteBuffer
import java.nio.ByteOrder;

public class Udp_Servidor{
    public static void main(String args[]){
        int port = 7200;
        try{
            DatagramSocket sock = new DatagramSocket(port);
            sock.setReuseAddress(true);
            while( true ){
                byte[] buffer = new byte[65536];
                DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
                sock.receive(reply);
                byte[] data = reply.getData();
                ByteBuffer buf = ByteBuffer.wrap(data);
                buf.order(ByteOrder.LITTLE_ENDIAN);
                float entero1 = buf.getFloat();
                float entero2 = buf.getFloat();
                System.out.println("int MIN = " + entero1 + " int MAX = " + entero2);
            }
        }catch(IOException e){
            System.err.println("IOException " + e);
        }
    }    
}   
