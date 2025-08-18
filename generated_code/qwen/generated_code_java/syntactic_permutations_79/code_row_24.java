import java.io.*;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        InputStream inputStream = System.in;

        int bytesRead = inputStream.read(buf, 0, 100);
        if (bytesRead != -1) {
            System.out.write(buf, 0, bytesRead);
        }

        bytesRead = inputStream.read(buf1, 0, 100);
        if (bytesRead != -1) {
            System.out.write(buf1, 0, bytesRead);
        }
    }
}