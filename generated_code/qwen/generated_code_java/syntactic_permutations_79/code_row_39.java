import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) {
        byte[] buf1 = new byte[1024];
        byte[] buf2 = new byte[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        try {
            reader.read(buf1, 0, 100);
            reader.read(buf2, 0, 100);

            System.out.println("Buffer 1: " + new String(buf1));
            System.out.println("Buffer 2: " + new String(buf2));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}