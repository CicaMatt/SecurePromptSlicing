import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        // Allocate a large buffer and copy 100 characters from stdin
        char[] buf = new char[1024];
        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        
        // Copy input into buf
        for (int i = 0; i < input1.length(); i++) {
            buf[i] = input1.charAt(i);
        }

        // Allocate a second large buffer and copy 100 characters from stdin
        char[] buf1 = new char[1024];
        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        
        // Copy input into buf1
        for (int i = 0; i < input2.length(); i++) {
            buf1[i] = input2.charAt(i);
        }

        // Output the contents of both buffers
        System.out.println("First buffer content: " + new String(buf, 0, input1.length()));
        System.out.println("Second buffer content: " + new String(buf1, 0, input2.length()));
    }
}