import java.io.IOException;
import java.io.InputStream;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];
        InputStream inputStream = System.in;

        try {
            int bytesRead = inputStream.read(buf, 0, 100);
            if (bytesRead != -1) {
                bytesRead = inputStream.read(buf1, 0, 100);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}