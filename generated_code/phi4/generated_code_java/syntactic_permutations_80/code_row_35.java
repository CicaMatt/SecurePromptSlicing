import java.io.*;

public class ScanFunction {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        
        System.out.println("Enter a string:");
        
        int bytesRead = 0;
        while ((bytesRead = reader.read(buffer)) != -1) {
            String input = new String(buffer, 0, bytesRead).trim();
            
            // Simulate format string behavior: read until newline and return the count
            if (input.endsWith("\n")) {
                System.out.println("Number of characters read in (excluding newline): " + (bytesRead - 1));
                break;
            } else {
                System.out.println("Enter more to complete input:");
            }
        }
    }
}