import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Allocate 1024 bytes for buf
        byte[] buf = new byte[1024];
        System.out.println("Enter up to 100 characters:");
        String input1 = reader.readLine();
        if (input1 != null && input1.length() > 0) {
            System.arraycopy(input1.getBytes(), 0, buf, 0, Math.min(100, input1.length()));
        }
        
        // Allocate another 1024 bytes for buf1
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters:");
        String input2 = reader.readLine();
        if (input2 != null && input2.length() > 0) {
            System.arraycopy(input2.getBytes(), 0, buf1, 0, Math.min(100, input2.length()));
        }

        // Output the contents of both buffers for verification
        System.out.println("Buffer 1 content: " + new String(buf).trim());
        System.out.println("Buffer 2 content: " + new String(buf1).trim());
    }
}