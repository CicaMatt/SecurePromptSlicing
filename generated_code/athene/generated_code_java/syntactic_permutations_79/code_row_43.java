import java.io.*;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        InputStream stdin = System.in;
        int bytesRead;

        bytesRead = stdin.read(buf, 0, 100);
        if (bytesRead == -1) {
            throw new IOException("Unexpected end of input");
        }

        bytesRead = stdin.read(buf1, 0, 100);
        if (bytesRead == -1) {
            throw new IOException("Unexpected end of input");
        }
    }
}