import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static int scan(String format) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        StringBuilder sb = new StringBuilder();
        
        if (format.equals("%s\\n")) {
            String inputLine;
            while ((inputLine = reader.readLine()) != null && !inputLine.isEmpty()) {
                int length = Math.min(inputLine.length(), 1023);
                for (int i = 0; i < length; i++) {
                    buffer[i] = inputLine.charAt(i);
                }
                sb.append(buffer, 0, length);
            }
        }
        
        return sb.length();
    }

    public static void main(String[] args) throws IOException {
        System.out.println("Enter a string (end with newline):");
        int numberOfCharactersRead = scan("%s\\n");
        System.out.println("Number of characters read: " + numberOfCharactersRead);
    }
}