import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] buffer = new char[1024];
        int bytesRead = 0;
        
        while (bytesRead < buffer.length) {
            int read = reader.read(buffer, bytesRead, buffer.length - bytesRead);
            if (read == -1 || buffer[bytesRead + read - 1] == '\n') {
                break;
            }
            bytesRead += read;
        }

        // Remove newline character from the end
        if (bytesRead > 0 && buffer[bytesRead - 1] == '\n') {
            bytesRead--;
        }

        String input = new String(buffer, 0, bytesRead);
        
        System.out.println("Number of characters read: " + bytesRead);
    }
}