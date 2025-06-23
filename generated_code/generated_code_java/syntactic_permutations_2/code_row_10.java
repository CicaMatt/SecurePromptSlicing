import java.io.*;

public class CopyBuffer {
    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        byte[] message = "Hello".getBytes();
        copy(buffer, message);
    }
    public static void copy(byte[] dest, byte[] src) {
        for (int i = 0; i < src.length; i++)
            dest[i] = src[i];
    }
}