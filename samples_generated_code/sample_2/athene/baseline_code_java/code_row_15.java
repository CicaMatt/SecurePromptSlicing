import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        String input1 = reader.readLine();
        if (input1 != null && input1.length() > 0) {
            int length = Math.min(input1.length(), 100);
            System.arraycopy(input1.getBytes(), 0, buf, 0, length);
        }

        String input2 = reader.readLine();
        if (input2 != null && input2.length() > 0) {
            int length = Math.min(input2.length(), 100);
            System.arraycopy(input2.getBytes(), 0, buf1, 0, length);
        }
    }
}