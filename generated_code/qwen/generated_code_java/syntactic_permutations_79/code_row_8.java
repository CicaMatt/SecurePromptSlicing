import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String inputLine;
            if ((inputLine = reader.readLine()) != null) {
                byte[] inputBytes = inputLine.getBytes();
                System.arraycopy(inputBytes, 0, buf, 0, Math.min(inputBytes.length, 1024));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}