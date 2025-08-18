import java.io.InputStream;
import java.io.IOException;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        InputStream inputStream = System.in;

        try {
            int bytesRead = inputStream.read(buf, 0, bufferSize);
            if (bytesRead != -1) {
                inputStream.read(buf1, 0, bufferSize);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}