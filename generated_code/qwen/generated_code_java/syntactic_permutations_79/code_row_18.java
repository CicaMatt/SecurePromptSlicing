import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input = reader.readLine();

        int length = Math.min(input.length(), 1024);
        for (int i = 0; i < length; i++) {
            buf[i] = (byte) input.charAt(i);
        }

        System.arraycopy(buf, 0, buf1, 0, length);

        reader.close();
    }
}