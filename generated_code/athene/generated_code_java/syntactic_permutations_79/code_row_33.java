import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() > 0) {
                int len = Math.min(input.length(), 100);
                System.arraycopy(input.getBytes(), 0, buf, 0, len);

                input = reader.readLine();
                if (input != null && input.length() > 0) {
                    len = Math.min(input.length(), 100);
                    System.arraycopy(input.getBytes(), 0, buf1, 0, len);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Output the content of the buffers to verify
        System.out.println(new String(buf).trim());
        System.out.println(new String(buf1).trim());
    }
}