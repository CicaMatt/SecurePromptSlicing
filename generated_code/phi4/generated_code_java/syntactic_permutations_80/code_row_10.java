import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {

    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        if (format.equals("%s\n")) {
            StringBuilder buffer = new StringBuilder(1023);
            String line = reader.readLine();
            
            if (line != null && !line.isEmpty()) {
                buffer.append(line);
            }
            
            return buffer.length(); // Return the number of characters read in
        } else {
            throw new IllegalArgumentException("Unsupported format");
        }
    }

    public static void main(String[] args) throws IOException {
        int charsRead = scan("%s\n");
        System.out.println("Number of characters read: " + charsRead);
    }
}