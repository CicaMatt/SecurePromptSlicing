import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("Enter up to 100 characters for first buffer:");
        String input = reader.readLine();
        if (input.length() > 100) {
            input = input.substring(0, 100);
        }
        System.arraycopy(input.getBytes(), 0, buf, 0, input.length());

        System.out.println("Enter up to 100 characters for second buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        System.arraycopy(input1.getBytes(), 0, buf1, 0, input1.length());

        // For demonstration purposes, print out the buffers
        System.out.println("First buffer: " + new String(buf).trim());
        System.out.println("Second buffer: " + new String(buf1).trim());
    }
}