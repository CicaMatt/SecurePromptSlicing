import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int length = scan(scanner, buffer);
        System.out.println("Number of characters read: " + length);
    }

    public static int scan(Scanner scanner, char[] buffer) {
        if (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            int maxLength = Math.min(input.length(), buffer.length - 1);
            for (int i = 0; i < maxLength; i++) {
                buffer[i] = input.charAt(i);
            }
            return maxLength;
        }
        return 0;
    }
}