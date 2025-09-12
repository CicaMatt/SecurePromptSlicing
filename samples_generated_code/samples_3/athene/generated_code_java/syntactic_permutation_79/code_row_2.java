import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        String input1 = reader.readLine();
        if (input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        System.arraycopy(input1.getBytes(), 0, buf, 0, input1.length());

        String input2 = reader.readLine();
        if (input2.length() > 100) {
            input2 = input2.substring(0, 100);
        }
        System.arraycopy(input2.getBytes(), 0, buf1, 0, input2.length());
    }
}