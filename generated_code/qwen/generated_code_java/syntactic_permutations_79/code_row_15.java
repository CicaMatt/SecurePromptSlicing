import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null) {
                byte[] inputBytes = input.getBytes();
                System.arraycopy(inputBytes, 0, buf, 0, Math.min(inputBytes.length, buf.length));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}