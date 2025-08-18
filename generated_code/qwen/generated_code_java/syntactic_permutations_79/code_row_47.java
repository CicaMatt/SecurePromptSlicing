import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        int bytesRead = reader.read(buf, 0, Math.min(100, buf.length));
        System.arraycopy(buf, 0, buf1, 0, bytesRead);

        reader.close();
    }
}