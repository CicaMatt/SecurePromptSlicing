import java.util.Scanner;

public class ScanFunction {
    public static int scan(String format) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        
        if (format.equals("%s")) {
            StringBuilder stringBuilder = new StringBuilder();
            while (scanner.hasNext() && count < 1023) {
                char ch = scanner.next().charAt(0);
                if (ch == '\n') break; // Stop reading at newline
                stringBuilder.append(ch);
                buffer[count++] = ch;
            }
            
            System.out.print(buffer, 0, count); // Output the read characters
            
        } else {
            throw new IllegalArgumentException("Unsupported format: " + format);
        }

        return count;
    }

    public static void main(String[] args) {
        int numCharsRead = scan("%s");
        System.out.println("\nNumber of characters read: " + numCharsRead);
    }
}