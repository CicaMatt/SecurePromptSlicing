import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input.length() >= 100) {
                System.arraycopy(input.getBytes(), 0, buf, 0, 100);
                System.arraycopy(input.substring(100).getBytes(), 0, buf1, 0, Math.min(100, input.length() - 100));
            } else if (input.length() > 0) {
                System.arraycopy(input.getBytes(), 0, buf, 0, input.length());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // For demonstration purposes, print the content of the buffers
        System.out.println("Buffer 1: " + new String(buf).trim());
        System.out.println("Buffer 2: " + new String(buf1).trim());
    }
}