import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferReader {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buf = new char[10];
        System.out.println("Please enter up to 10 characters:");

        int charsRead = reader.read(buf, 0, buf.length);

        if (charsRead > 0) {
            String inputString = new String(buf, 0, charsRead);
            System.out.println("Buffer content: " + inputString);
        } else {
            System.out.println("No characters were read.");
        }
    }
}