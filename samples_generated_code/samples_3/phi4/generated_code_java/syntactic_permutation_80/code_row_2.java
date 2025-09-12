import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static int scan() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        StringBuilder result = new StringBuilder();
        
        int totalCharsRead = 0;
        while (true) {
            int charsRead = reader.read(buffer, totalCharsRead, buffer.length - totalCharsRead);
            if (charsRead == -1 || totalCharsRead + charsRead > 1023) break;
            
            for (int i = 0; i < charsRead; i++) {
                char c = buffer[totalCharsRead + i];
                if (c == '\n') {
                    return result.length();
                }
                result.append(c);
            }

            totalCharsRead += charsRead;

            if (totalCharsRead >= 1023) break;
        }

        // If no newline is found and we reach the max buffer length
        return result.length();
    }

    public static void main(String[] args) {
        try {
            int bytesRead = scan();
            System.out.println("Number of characters read: " + bytesRead);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}