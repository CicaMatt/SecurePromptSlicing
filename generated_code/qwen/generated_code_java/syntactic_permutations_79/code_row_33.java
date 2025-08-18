import java.io.*;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        InputStream is = System.in;

        int bytesReadFirst = is.read(buf, 0, 100);
        if (bytesReadFirst > 0) {
            System.out.write(buf, 0, bytesReadFirst);
        }

        int bytesReadSecond = is.read(buf1, 0, 100);
        if (bytesReadSecond > 0) {
            System.out.write(buf1, 0, bytesReadSecond);
        }
    }
}