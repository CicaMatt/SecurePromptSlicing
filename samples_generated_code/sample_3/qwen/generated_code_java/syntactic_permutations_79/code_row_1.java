import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] secondBuf = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String firstInput = reader.readLine();
            String secondInput = reader.readLine();

            System.arraycopy(firstInput.getBytes(), 0, buf, 0, Math.min(100, firstInput.length()));
            System.arraycopy(secondInput.getBytes(), 0, secondBuf, 0, Math.min(100, secondInput.length()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}