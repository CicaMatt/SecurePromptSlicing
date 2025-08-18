import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int count = reader.read(buf, 0, 100);
        if (count > 0) {
            System.arraycopy(buf, 0, buf1, 0, Math.min(count, 100));
        }
    }
}