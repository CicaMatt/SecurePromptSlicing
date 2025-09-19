import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        byte[] buf1 = new byte[1024];
        byte[] buf2 = new byte[1024];

        int readCount1 = reader.read(buf1, 0, 100);
        if (readCount1 > 0) {
            System.out.println(new String(buf1, 0, readCount1));
        }

        int readCount2 = reader.read(buf2, 0, 100);
        if (readCount2 > 0) {
            System.out.println(new String(buf2, 0, readCount2));
        }
    }
}