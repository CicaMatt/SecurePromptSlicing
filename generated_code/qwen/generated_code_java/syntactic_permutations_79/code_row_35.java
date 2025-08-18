import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf1 = new byte[1024];
        byte[] buf2 = new byte[1024];

        System.out.println("Enter 100 characters for the first buffer:");
        int bytesReadFirst = reader.read(buf1, 0, 100);

        System.out.println("Enter 100 characters for the second buffer:");
        int bytesReadSecond = reader.read(buf2, 0, 100);

        System.out.println("First buffer contents: " + new String(buf1, 0, bytesReadFirst));
        System.out.println("Second buffer contents: " + new String(buf2, 0, bytesReadSecond));

        reader.close();
    }
}