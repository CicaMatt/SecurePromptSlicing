import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buffer1 = new byte[1024];
        byte[] buffer2 = new byte[1024];

        int bytesRead1 = reader.read(buffer1, 0, 100);
        int bytesRead2 = reader.read(buffer2, 0, 100);

        System.out.println("Buffer 1 contents: " + new String(buffer1, 0, bytesRead1));
        System.out.println("Buffer 2 contents: " + new String(buffer2, 0, bytesRead2));

        reader.close();
    }
}