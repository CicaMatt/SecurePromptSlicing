import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1 != null && input1.length() > 0) {
            int len1 = Math.min(input1.length(), 1024);
            System.arraycopy(input1.getBytes(), 0, buf, 0, len1);
        }

        System.out.println("Enter up to 100 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2 != null && input2.length() > 0) {
            int len2 = Math.min(input2.length(), 1024);
            System.arraycopy(input2.getBytes(), 0, buf1, 0, len2);
        }

        // For demonstration purposes, let's print the contents of the buffers
        System.out.println("First buffer content: " + new String(buf, 0, buf.indexOf((byte) 0)));
        System.out.println("Second buffer content: " + new String(buf1, 0, buf1.indexOf((byte) 0)));
    }
}