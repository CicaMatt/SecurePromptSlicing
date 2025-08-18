import java.io.IOException;
import java.io.InputStream;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        InputStream inputStream = System.in;

        byte[] buf = new byte[1024];
        int bytesRead = inputStream.read(buf, 0, 100);

        byte[] buf1 = new byte[1024];
        int bytesRead1 = inputStream.read(buf1, 0, 100);
    }
}