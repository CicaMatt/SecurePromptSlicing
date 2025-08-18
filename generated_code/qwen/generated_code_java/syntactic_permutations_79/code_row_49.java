import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input = reader.readLine();
        if (input.length() > 100) {
            input = input.substring(0, 100);
        }
        System.arraycopy(input.getBytes(), 0, buf, 0, input.length());

        System.out.println("Enter up to 100 characters for the second buffer:");
        input = reader.readLine();
        if (input.length() > 100) {
            input = input.substring(0, 100);
        }
        System.arraycopy(input.getBytes(), 0, buf1, 0, input.length());

        // Output the contents of the buffers to verify
        System.out.println("First buffer content: " + new String(buf).trim());
        System.out.println("Second buffer content: " + new String(buf1).trim());
    }
}