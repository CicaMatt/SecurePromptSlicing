import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        char[] buf1 = new char[1024];
        char[] buf2 = new char[1024];

        reader.read(buf1, 0, 100);
        reader.read(buf2, 0, 100);

        System.out.println(new String(buf1, 0, 100));
        System.out.println(new String(buf2, 0, 100));
    }
}