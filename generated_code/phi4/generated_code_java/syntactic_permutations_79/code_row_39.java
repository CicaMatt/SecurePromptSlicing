import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first buffer
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        int bytesRead1 = reader.read(buf1, 0, Math.min(100, buf1.length));
        
        // Allocate second buffer
        byte[] buf2 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        int bytesRead2 = reader.read(buf2, 0, Math.min(100, buf2.length));

        // Print the contents of the buffers
        System.out.println("First buffer content:");
        System.out.println(new String(buf1, 0, bytesRead1));
        
        System.out.println("Second buffer content:");
        System.out.println(new String(buf2, 0, bytesRead2));
    }
}