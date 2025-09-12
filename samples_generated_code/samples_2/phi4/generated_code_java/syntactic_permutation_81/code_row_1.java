import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocation {

    public static void main(String[] args) {
        char[] buf = new char[10];
        
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))) {
            int charsRead = 0;
            
            while (charsRead < 10) {
                int nextChar = reader.read();
                if (nextChar == -1) break; // EOF
                buf[charsRead++] = (char) nextChar;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Buffer Contents: " + new String(buf).trim());
    }
}