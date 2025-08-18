import java.util.Scanner;

public class ScanExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = scan(scanner, buffer);
        System.out.println("Number of characters read: " + count);
        System.out.print("Read string: ");
        for (int i = 0; i < count; i++) {
            System.out.print(buffer[i]);
        }
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