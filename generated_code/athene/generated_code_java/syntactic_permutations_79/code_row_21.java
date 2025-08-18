import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        char[] buf = new char[1024];
        int charsRead = reader.read(buf, 0, 100);
        if (charsRead > 0) {
            System.out.println("First buffer: " + new String(buf, 0, charsRead));
        }

        char[] buf1 = new char[1024];
        charsRead = reader.read(buf1, 0, 100);
        if (charsRead > 0) {
            System.out.println("Second buffer: " + new String(buf1, 0, charsRead));
        }
    }
}