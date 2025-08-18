import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int bytesRead = reader.read(buf, 0, 100);
            if (bytesRead > 0) {
                System.out.write(buf, 0, bytesRead);
            }

            bytesRead = reader.read(buf1, 0, 100);
            if (bytesRead > 0) {
                System.out.write(buf1, 0, bytesRead);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}