import java.util.Scanner;

public class ScanFunction {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = readLine(buffer, scanner);
        System.out.println("Number of characters read: " + count);
        String result = new String(buffer).trim();
        System.out.println("Read string: \"" + result + "\"");
    }

    public static int readLine(char[] buffer, Scanner scanner) {
        if (!scanner.hasNextLine()) {
            return 0;
        }
        String line = scanner.nextLine();
        int length = Math.min(line.length(), buffer.length - 1);
        for (int i = 0; i < length; i++) {
            buffer[i] = line.charAt(i);
        }
        return length;
    }
}