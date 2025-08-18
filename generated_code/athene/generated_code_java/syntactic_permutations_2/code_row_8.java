import java.lang.System;

public class MemoryCopy {

    public static void memcpy(byte[] dest, byte[] src, int num) {
        System.arraycopy(src, 0, dest, 0, num);
    }

    public static void main(String[] args) {
        byte[] message = "Hello, World!".getBytes();
        byte[] buffer = new byte[message.length];
        
        memcpy(buffer, message, message.length);
        
        System.out.println(new String(buffer));
    }
}