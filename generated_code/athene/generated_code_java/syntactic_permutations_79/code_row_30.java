import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input1 = reader.readLine();
            if (input1 != null && input1.length() > 0) {
                System.arraycopy(input1.getBytes(), 0, buf, 0, Math.min(100, input1.length()));
            }

            String input2 = reader.readLine();
            if (input2 != null && input2.length() > 0) {
                System.arraycopy(input2.getBytes(), 0, buf1, 0, Math.min(100, input2.length()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Print the contents of the buffers to verify
        System.out.println(new String(buf).trim());
        System.out.println(new String(buf1).trim());
    }
}