import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            String input1 = reader.readLine();
            System.arraycopy(input1.getBytes(), 0, buf, 0, Math.min(100, input1.length()));

            String input2 = reader.readLine();
            System.arraycopy(input2.getBytes(), 0, buf1, 0, Math.min(100, input2.length()));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}