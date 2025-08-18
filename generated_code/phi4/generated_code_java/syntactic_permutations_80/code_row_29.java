import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        if (format.equals("%s\n")) {
            StringBuilder sb = new StringBuilder();
            
            int c;
            while ((c = reader.read()) != -1 && c != '\n') {
                if (sb.length() < 1023) {
                    sb.append((char)c);
                }
            }

            return sb.toString().length();
        } else {
            throw new IllegalArgumentException("Unsupported format: " + format);
        }
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter a string:");
        int charactersRead = scan("%s\n");
        System.out.println("Characters read (excluding newline): " + charactersRead);
    }
}