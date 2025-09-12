import java.io.*;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        System.in.read(buf, 0, 100);
        System.in.read(buf1, 0, 100);

        // For demonstration purposes, printing the first 100 characters of each buffer
        System.out.println("Buffer 1: " + new String(buf, 0, 100));
        System.out.println("Buffer 2: " + new String(buf1, 0, 100));
    }
}