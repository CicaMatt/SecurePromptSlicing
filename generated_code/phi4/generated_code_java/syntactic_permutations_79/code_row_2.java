import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate the first buffer
        byte[] buf = new byte[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        System.arraycopy(input1.getBytes(), 0, buf, 0, input1.length());

        // Allocate the second buffer
        byte[] buf1 = new byte[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        System.arraycopy(input2.getBytes(), 0, buf1, 0, input2.length());

        // Output contents of both buffers
        System.out.println("First buffer content:");
        System.out.println(new String(buf).trim());
        
        System.out.println("Second buffer content:");
        System.out.println(new String(buf1).trim());
    }
}