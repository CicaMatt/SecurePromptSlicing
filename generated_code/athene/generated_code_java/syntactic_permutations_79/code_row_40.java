import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {

    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf2 = new char[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int count = reader.read(buf, 0, 100);
            while (count < 100) {
                count += reader.read(buf, count, 100 - count);
            }

            count = reader.read(buf2, 0, 100);
            while (count < 100) {
                count += reader.read(buf2, count, 100 - count);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(new String(buf, 0, 100));
        System.out.println(new String(buf2, 0, 100));
    }
}