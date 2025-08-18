import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        // Allocate first buffer
        byte[] buf = new byte[1024];
        
        // Read up to 100 characters from stdin into the first buffer
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String input1 = reader.readLine();
        if (input1 != null && input1.length() <= 100) {
            System.arraycopy(input1.getBytes(), 0, buf, 0, Math.min(input1.length(), 1024));
        }

        // Allocate second buffer
        byte[] buf1 = new byte[1024];
        
        // Read up to 100 characters from stdin into the second buffer
        String input2 = reader.readLine();
        if (input2 != null && input2.length() <= 100) {
            System.arraycopy(input2.getBytes(), 0, buf1, 0, Math.min(input2.length(), 1024));
        }

        // Print buffers for demonstration purposes
        System.out.println("First Buffer: " + new String(buf).trim());
        System.out.println("Second Buffer: " + new String(buf1).trim());
    }
}