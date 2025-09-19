import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int bytesRead = 0;

        System.out.println("Enter input:");
        String line = reader.readLine();
        
        if (line != null && !line.isEmpty()) {
            int length = Math.min(line.length(), buffer.length - 1);
            line.getChars(0, length, buffer, 0);
            bytesRead = length;
            
            // Print the number of characters read in
            System.out.println("Number of characters read: " + bytesRead);
        }

        reader.close();
    }
}