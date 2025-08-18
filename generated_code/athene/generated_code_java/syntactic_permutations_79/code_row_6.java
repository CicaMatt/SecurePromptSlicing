import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];
        System.in.read(buf, 0, 100);
        System.in.read(buf1, 0, 100);
    }
}