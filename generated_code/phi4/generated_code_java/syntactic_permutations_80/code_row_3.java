import java.util.Scanner;

public class InputScanner {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Create a buffer of size 1024
        char[] buffer = new char[1024];
        
        // Read input until newline or limit is reached
        int count = scanner.read(buffer, 0, 1023);

        if (count > 0) {
            // Adjust to null-terminate the string
            buffer[count] = '\0';
            
            // Convert the char array to String
            String inputString = new String(buffer).trim();
            
            System.out.println("Number of characters read: " + count);
            System.out.println("Input string: " + inputString);
        } else {
            System.out.println("No input was provided or an error occurred.");
        }
        
        scanner.close();
    }
}