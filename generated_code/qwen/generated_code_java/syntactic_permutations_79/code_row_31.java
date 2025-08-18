import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            byte[] inputBytes = input.getBytes();

            System.arraycopy(inputBytes, 0, buf, 0, Math.min(100, inputBytes.length));
            if (inputBytes.length > 100) {
                System.arraycopy(inputBytes, 100, buf1, 0, Math.min(100, inputBytes.length - 100));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}