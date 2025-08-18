import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int readCount = scan(scanner, buffer);
        System.out.println("Number of characters read: " + readCount);
    }

    public static int scan(Scanner scanner, char[] buffer) {
        if (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            int length = Math.min(line.length(), buffer.length - 1);
            for (int i = 0; i < length; i++) {
                buffer[i] = line.charAt(i);
            }
            return length;
        }
        return 0;
    }
}