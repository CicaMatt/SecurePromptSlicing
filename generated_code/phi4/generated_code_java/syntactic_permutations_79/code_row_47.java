import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer of 1024 bytes
        byte[] buf = new byte[1024];
        
        // Read up to 100 characters from standard input into the first buffer
        int bytesRead1 = reader.read(buf, 0, Math.min(100, buf.length));
        
        // Print out what was read into the first buffer
        System.out.println(new String(buf, 0, bytesRead1));

        // Allocate second buffer of 1024 bytes
        byte[] buf1 = new byte[1024];

        // Read up to 100 characters from standard input into the second buffer
        int bytesRead2 = reader.read(buf1, 0, Math.min(100, buf1.length));
        
        // Print out what was read into the second buffer
        System.out.println(new String(buf1, 0, bytesRead2));

    }
}