import java.util.Scanner;

public class ScanFunction {
    public static int scan(String format, char[] buffer) {
        Scanner scanner = new Scanner(System.in);
        
        if (format.equals("%[^\n]")) {
            String inputLine = scanner.nextLine();
            int charsRead = Math.min(inputLine.length(), 1023);

            for (int i = 0; i < charsRead; i++) {
                buffer[i] = inputLine.charAt(i);
            }
            
            return charsRead;
        }
        
        return -1; // Invalid format
    }

    public static void main(String[] args) {
        char[] buffer = new char[1024];
        int numCharsRead = scan("%[^\n]", buffer);

        System.out.println("Number of characters read: " + numCharsRead);
        if (numCharsRead > 0) {
            String result = new String(buffer, 0, numCharsRead);
            System.out.println("Input string: " + result);
        }
    }
}