import java.io.InputStream;
import java.io.IOException;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        InputStream inputStream = System.in;
        
        byte[] buf = new byte[1024];
        int bytesRead = inputStream.read(buf, 0, 100);
        if (bytesRead > 0) {
            String firstInput = new String(buf, 0, bytesRead);
            System.out.println("First Input: " + firstInput);
        }

        byte[] buf1 = new byte[1024];
        bytesRead = inputStream.read(buf1, 0, 100);
        if (bytesRead > 0) {
            String secondInput = new String(buf1, 0, bytesRead);
            System.out.println("Second Input: " + secondInput);
        }
    }
}