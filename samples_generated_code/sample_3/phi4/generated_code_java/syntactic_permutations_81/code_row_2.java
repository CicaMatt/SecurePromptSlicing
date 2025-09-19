import java.io.*;

public class BufferAllocator {
    public static void main(String[] args) {
        char[] buf = new char[10];
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() >= 10) {
                System.arraycopy(input.toCharArray(), 0, buf, 0, 10);
            } else if (input != null) {
                System.arraycopy(input.toCharArray(), 0, buf, 0, input.length());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Output the buffer content for verification
        System.out.println(new String(buf));
    }
}