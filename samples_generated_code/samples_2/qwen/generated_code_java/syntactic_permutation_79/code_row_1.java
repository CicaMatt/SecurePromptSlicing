import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocator {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        reader.read(buf, 0, 100);

        byte[] buf1 = new byte[1024];
        reader.read(buf1, 0, 100);
    }
}