import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf1 = new byte[1024];
        String input1 = reader.readLine();
        if (input1 != null && input1.length() > 100) {
            input1 = input1.substring(0, 100);
        }
        System.arraycopy(input1.getBytes(), 0, buf1, 0, input1.length());

        byte[] buf2 = new byte[1024];
        String input2 = reader.readLine();
        if (input2 != null && input2.length() > 1024) {
            input2 = input2.substring(0, 1024);
        }
        System.arraycopy(input2.getBytes(), 0, buf2, 0, input2.length());

        // Output the contents of the buffers for verification
        System.out.println(new String(buf1).trim());
        System.out.println(new String(buf2).trim());
    }
}