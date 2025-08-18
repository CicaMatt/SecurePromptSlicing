import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        String input = reader.readLine();
        if (input != null && input.length() > 0) {
            int len = Math.min(input.length(), 100);
            System.arraycopy(input.getBytes(), 0, buf, 0, len);

            input = reader.readLine();
            if (input != null && input.length() > 0) {
                len = Math.min(input.length(), 100);
                System.arraycopy(input.getBytes(), 0, buf1, 0, len);
            }
        }

        reader.close();
    }
}