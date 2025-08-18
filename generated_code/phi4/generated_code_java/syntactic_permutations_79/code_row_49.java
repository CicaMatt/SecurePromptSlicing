import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        // Read up to 100 characters from standard input and store in buf
        int bytesRead = reader.read(buf, 0, 100);
        if (bytesRead > 0) {
            System.out.println("First buffer content: " + new String(buf, 0, bytesRead));
        }

        // Read up to 100 characters from standard input and store in buf1
        bytesRead = reader.read(buf1, 0, 100);
        if (bytesRead > 0) {
            System.out.println("Second buffer content: " + new String(buf1, 0, bytesRead));
        }
    }
}