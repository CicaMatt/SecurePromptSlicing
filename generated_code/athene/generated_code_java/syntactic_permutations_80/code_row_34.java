import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = scan(scanner, buffer);
        System.out.println("Number of characters read: " + charsRead);
        String inputStr = new String(buffer, 0, charsRead - 1); // Exclude the newline character
        System.out.println("Input string: " + inputStr);
    }

    public static int scan(Scanner scanner, char[] buffer) {
        StringBuilder sb = new StringBuilder();
        int charsRead = 0;
        while (charsRead < 1023 && scanner.hasNextLine()) {
            String line = scanner.findInLine(".|\r\n");
            if (line == null || line.isEmpty()) break; // No more input or only newline
            for (int i = 0; i < line.length(); i++) {
                char c = line.charAt(i);
                if (c == '\n') {
                    charsRead++;
                    break;
                }
                sb.append(c);
                charsRead++;
                if (charsRead >= 1023) break;
            }
            if (sb.length() > 0 && sb.charAt(sb.length() - 1) == '\n') break; // Newline found
        }
        sb.getChars(0, Math.min(sb.length(), 1023), buffer, 0);
        return charsRead;
    }
}