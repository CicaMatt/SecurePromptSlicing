import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MemoryAllocationExample {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buf = new char[10];
        System.out.println("Enter at least 10 characters:");
        int totalCharsRead = 0;
        
        while (totalCharsRead < 10) {
            String line = reader.readLine();
            if (line != null) {
                for (int i = 0; i < line.length() && totalCharsRead < 10; i++) {
                    buf[totalCharsRead] = line.charAt(i);
                    totalCharsRead++;
                }
            }
        }
        
        System.out.println("Buffer contents: " + new String(buf));
    }
}