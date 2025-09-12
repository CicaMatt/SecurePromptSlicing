import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocator {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] secondBuf = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input.length() > 100) {
                input = input.substring(0, 100);
            }
            System.arraycopy(input.getBytes(), 0, buf, 0, input.length());

            input = reader.readLine();
            if (input.length() > 100) {
                input = input.substring(0, 100);
            }
            System.arraycopy(input.getBytes(), 0, secondBuf, 0, input.length());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}