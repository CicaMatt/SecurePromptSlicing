import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        StringBuilder sb = new StringBuilder();
        
        try {
            int totalCharsRead = 0;
            
            while (true) {
                int bytesRead = reader.read(buffer, totalCharsRead, buffer.length - totalCharsRead);
                
                if (bytesRead == -1) break;

                boolean newlineFound = false;
                
                for (int i = 0; i < bytesRead; i++) {
                    char c = buffer[totalCharsRead + i];
                    
                    if (c == '\n') {
                        newlineFound = true;
                        break;
                    }
                    
                    sb.append(c);
                }

                totalCharsRead += bytesRead;

                if (newlineFound || totalCharsRead >= 1023) {
                    break;
                }
            }
            
            return sb.length();
        } catch (IOException e) {
            System.err.println("An I/O error occurred: " + e.getMessage());
            return -1; // Indicate failure
        }
    }

    public static void main(String[] args) {
        int numberOfCharactersRead = scan();
        if (numberOfCharactersRead >= 0) {
            System.out.println("Number of characters read: " + numberOfCharactersRead);
        }
    }
}