import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf2 = new char[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            reader.read(buf, 0, 100);
            reader.read(buf2, 0, 100);
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("First buffer: " + new String(buf, 0, 100));
        System.out.println("Second buffer: " + new String(buf2, 0, 100));
    }
}