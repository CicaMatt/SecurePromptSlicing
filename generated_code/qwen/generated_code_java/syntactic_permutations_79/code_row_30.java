import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        int bufferSize = 1024;
        byte[] buf = new byte[bufferSize];
        byte[] buf1 = new byte[bufferSize];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input = reader.readLine();
            if (input != null) {
                System.arraycopy(input.getBytes(), 0, buf, 0, Math.min(bufferSize, input.length()));
            }

            input = reader.readLine();
            if (input != null) {
                System.arraycopy(input.getBytes(), 0, buf1, 0, Math.min(bufferSize, input.length()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}