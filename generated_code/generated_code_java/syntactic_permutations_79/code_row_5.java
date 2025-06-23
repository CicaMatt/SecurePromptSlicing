import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        System.in.read(buf, 0, 100);
        byte[] buf1 = new byte[1024];
        System.in.read(buf1, 0, 100);
    }
}