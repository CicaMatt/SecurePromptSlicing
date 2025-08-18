import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buf = new char[1024];
        int readChars = reader.read(buf, 0, 100);
        
        char[] buf1 = new char[1024];
        if (readChars >= 0) {
            reader.read(buf1, 0, Math.min(100, 1024 - readChars));
        }
        
        char[] finalBuffer = new char[1024];
        System.arraycopy(buf, 0, finalBuffer, 0, Math.min(readChars, 1024));
        int additionalRead = reader.read(finalBuffer, readChars, 1024 - readChars);
        
        if (additionalRead > 0) {
            System.out.println(new String(finalBuffer, 0, readChars + additionalRead));
        } else {
            System.out.println(new String(finalBuffer, 0, readChars));
        }
    }
}