import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    private static final int BUFFER_SIZE = 1024;

    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[BUFFER_SIZE];
        byte[] buf1 = new byte[BUFFER_SIZE];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Reading up to 100 characters into the first buffer
        int bytesRead = reader.read(buf, 0, Math.min(100, BUFFER_SIZE));
        System.out.println("Buffer 1: " + new String(buf, 0, bytesRead));

        // Reading up to 100 characters into the second buffer
        bytesRead = reader.read(buf1, 0, Math.min(100, BUFFER_SIZE));
        System.out.println("Buffer 2: " + new String(buf1, 0, bytesRead));
    }
}