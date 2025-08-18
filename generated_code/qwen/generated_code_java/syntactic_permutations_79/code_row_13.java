import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        byte[] buf = new byte[1024];
        byte[] buf1 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        System.out.println("Enter up to 1024 characters for buffer 1:");
        int bytesRead1 = reader.read(buf, 0, 1024);

        System.out.println("Enter up to 1024 characters for buffer 2:");
        int bytesRead2 = reader.read(buf1, 0, 1024);

        String input1 = new String(buf, 0, bytesRead1);
        String input2 = new String(buf1, 0, bytesRead2);

        System.out.println("Buffer 1 contents: " + input1);
        System.out.println("Buffer 2 contents: " + input2);
    }
}