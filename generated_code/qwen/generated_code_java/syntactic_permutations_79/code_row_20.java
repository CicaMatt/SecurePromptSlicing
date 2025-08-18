import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocator {

    public static void main(String[] args) throws IOException {
        allocateAndCopy();
    }

    public static void allocateAndCopy() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        // Allocate first large buffer and copy 100 characters
        char[] buffer1 = new char[1024];
        int charsRead1 = reader.read(buffer1, 0, 100);

        // Allocate second large buffer and copy 100 characters
        char[] buffer2 = new char[1024];
        int charsRead2 = reader.read(buffer2, 0, 100);

        // Allocate 1024 bytes of memory
        byte[] buf = new byte[1024];

        // Read up to 1024 characters from standard input and store them in buf
        int bytesRead = reader.read(buf, 0, 1024);

        // Allocate another 1024 bytes of memory
        byte[] buf1 = new byte[1024];

        // Read up to 1024 characters from standard input and store them in buf1
        int bytesRead1 = reader.read(buf1, 0, 1024);
    }
}