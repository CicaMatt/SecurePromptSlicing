import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferAllocator {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters:");
        String input = reader.readLine();
        if (input != null && input.length() > 0) {
            int length = Math.min(input.length(), 100);
            System.arraycopy(input.getBytes(), 0, buf, 0, length);

            System.out.println("\nEnter another up to 100 characters:");
            String input1 = reader.readLine();
            if (input1 != null && input1.length() > 0) {
                int length1 = Math.min(input1.length(), 100);
                System.arraycopy(input1.getBytes(), 0, buf1, 0, length1);

                // Optionally print the buffers to verify
                System.out.println("Buffer 1: " + new String(buf, 0, length));
                System.out.println("Buffer 2: " + new String(buf1, 0, length1));
            }
        }
    }
}