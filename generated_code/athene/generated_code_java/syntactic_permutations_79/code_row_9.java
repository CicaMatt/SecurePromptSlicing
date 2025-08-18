import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int readCount = reader.read(buf, 0, 1024);
            if (readCount > 0) {
                System.out.println("First buffer content: " + new String(buf, 0, readCount));
            }

            readCount = reader.read(buf1, 0, 1024);
            if (readCount > 0) {
                System.out.println("Second buffer content: " + new String(buf1, 0, readCount));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}