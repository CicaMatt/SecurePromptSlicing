import java.io.IOException;
import java.io.InputStream;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        InputStream inputStream = System.in;

        int bytesReadFirst = inputStream.read(buf, 0, 100);
        if (bytesReadFirst > 0) {
            System.out.write(buf, 0, bytesReadFirst);
        }

        int bytesReadSecond = inputStream.read(buf1, 0, 100);
        if (bytesReadSecond > 0) {
            System.out.write(buf1, 0, bytesReadSecond);
        }
    }
}