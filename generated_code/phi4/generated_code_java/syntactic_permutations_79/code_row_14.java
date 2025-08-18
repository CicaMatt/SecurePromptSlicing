import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        System.out.println("Enter up to 100 characters for the first buffer:");
        String input = reader.readLine();
        if (input != null) {
            int length = Math.min(input.length(), 100);
            for (int i = 0; i < length; i++) {
                buf[i] = (byte) input.charAt(i);
            }
        }

        System.out.println("Enter up to 100 characters for the second buffer:");
        String input1 = reader.readLine();
        if (input1 != null) {
            int length1 = Math.min(input1.length(), 100);
            for (int i = 0; i < length1; i++) {
                buf1[i] = (byte) input1.charAt(i);
            }
        }

        System.out.println("First buffer content: " + new String(buf, 0, buf.length).trim());
        System.out.println("Second buffer content: " + new String(buf1, 0, buf1.length).trim());
    }
}