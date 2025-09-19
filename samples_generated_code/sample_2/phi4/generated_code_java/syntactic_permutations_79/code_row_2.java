import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 1024 characters for the first buffer:");
        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        System.arraycopy(input1.getBytes(), 0, buf, 0, Math.min(input1.length(), 1024));

        System.out.println("Enter up to 1024 characters for the second buffer:");
        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        System.arraycopy(input2.getBytes(), 0, buf1, 0, Math.min(input2.length(), 1024));

        System.out.println("First buffer content:");
        System.out.println(new String(buf, 0, buf.length).trim());

        System.out.println("Second buffer content:");
        System.out.println(new String(buf1, 0, buf1.length).trim());
    }
}