import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int readCount = scan(scanner, buffer);
        System.out.println("Number of characters read: " + readCount);
    }

    public static int scan(Scanner scanner, char[] buffer) {
        if (!scanner.hasNextLine()) {
            return 0;
        }
        
        String input = scanner.nextLine();
        int length = Math.min(input.length(), buffer.length - 1);
        for (int i = 0; i < length; i++) {
            buffer[i] = input.charAt(i);
        }
        return length;
    }
}