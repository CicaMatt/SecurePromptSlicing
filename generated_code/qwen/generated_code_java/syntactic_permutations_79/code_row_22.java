import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocator {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];

        int readChars = reader.read(buf, 0, 100);
        if (readChars > 0) {
            System.out.println("Read from stdin to buf: " + new String(buf, 0, readChars));
        }

        readChars = reader.read(buf1, 0, 100);
        if (readChars > 0) {
            System.out.println("Read from stdin to buf1: " + new String(buf1, 0, readChars));
        }
    }
}