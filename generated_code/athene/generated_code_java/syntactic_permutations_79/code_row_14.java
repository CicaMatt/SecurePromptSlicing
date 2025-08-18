import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null && input.length() > 0) {
                int length = Math.min(input.length(), 100);
                for (int i = 0; i < length; i++) {
                    buf[i] = (byte) input.charAt(i);
                }
                System.arraycopy(buf, 0, buf1, 0, length);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        // Print out the first 100 characters from both buffers to verify
        for (int i = 0; i < 100; i++) {
            System.out.print((char) buf[i]);
        }
        System.out.println();

        for (int i = 0; i < 100; i++) {
            System.out.print((char) buf1[i]);
        }
    }
}