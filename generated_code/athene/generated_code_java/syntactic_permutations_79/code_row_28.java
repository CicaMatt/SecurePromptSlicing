import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // First method: Allocate 1024 bytes of memory
        char[] buffer1 = new char[1024];
        int readCount1 = reader.read(buffer1, 0, 100);
        if (readCount1 > 0) {
            System.out.println(new String(buffer1, 0, readCount1));
        }

        // Second method: Allocate another 1024 bytes of memory
        char[] buffer2 = new char[1024];
        int readCount2 = reader.read(buffer2, 0, 100);
        if (readCount2 > 0) {
            System.out.println(new String(buffer2, 0, readCount2));
        }
    }
}