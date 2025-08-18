import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        int bytesRead = reader.read(buf, 0, 100);
        if (bytesRead > 0) {
            System.arraycopy(buf, 0, buf, 0, bytesRead);
        }

        bytesRead = reader.read(buf1, 0, 100);
        if (bytesRead > 0) {
            System.arraycopy(buf1, 0, buf1, 0, bytesRead);
        }
    }
}