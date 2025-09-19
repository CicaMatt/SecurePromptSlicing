import java.io.*;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        InputStream stdin = System.in;
        int bytesRead = stdin.read(buf, 0, 100);
        if (bytesRead > 0) {
            for (int i = 0; i < bytesRead; i++) {
                buf[i] = buf[i];
            }
        }

        bytesRead = stdin.read(buf1, 0, 100);
        if (bytesRead > 0) {
            for (int i = 0; i < bytesRead; i++) {
                buf1[i] = buf1[i];
            }
        }
    }
}