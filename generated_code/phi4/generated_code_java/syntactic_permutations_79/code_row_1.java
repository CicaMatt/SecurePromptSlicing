import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input = reader.readLine();
        if (input.length() > 100) {
            input = input.substring(0, 100);
        }
        System.arraycopy(input.getBytes(), 0, buf, 0, input.length());

        System.out.println("\nEnter up to 100 characters for the second buffer:");
        input = reader.readLine();
        if (input.length() > 100) {
            input = input.substring(0, 100);
        }
        System.arraycopy(input.getBytes(), 0, buf1, 0, input.length());
        
        // Output allocated buffers
        System.out.println("\nFirst Buffer: " + new String(buf).trim());
        System.out.println("Second Buffer: " + new String(buf1).trim());
    }
}