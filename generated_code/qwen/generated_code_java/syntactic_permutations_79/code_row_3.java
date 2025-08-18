import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        String input = reader.readLine();
        System.arraycopy(input.getBytes(), 0, buf, 0, Math.min(100, input.length()));

        input = reader.readLine();
        System.arraycopy(input.getBytes(), 0, buf1, 0, Math.min(100, input.length()));
    }
}