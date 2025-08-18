import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        int count = reader.read(buf, 0, 100);
        while (count < 100) {
            count += reader.read(buf, count, 100 - count);
        }

        count = reader.read(buf1, 0, 100);
        while (count < 100) {
            count += reader.read(buf1, count, 100 - count);
        }
    }
}