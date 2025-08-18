import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        System.out.println("Enter up to 1024 characters for the first buffer:");
        int bytesRead1 = reader.read(buf, 0, buf.length);
        if (bytesRead1 > 0) {
            String input1 = new String(buf, 0, bytesRead1);
            System.out.println("First buffer content: " + input1);
        }

        System.out.println("Enter up to 1024 characters for the second buffer:");
        int bytesRead2 = reader.read(buf1, 0, buf1.length);
        if (bytesRead2 > 0) {
            String input2 = new String(buf1, 0, bytesRead2);
            System.out.println("Second buffer content: " + input2);
        }
    }
}