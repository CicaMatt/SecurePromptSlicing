import java.util.Scanner;

public class InputScanner {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.length() > 1023) {
                line = line.substring(0, 1023);
            }
            for (int i = 0; i < line.length(); i++) {
                buffer[count++] = line.charAt(i);
            }
            break;
        }
        System.out.println("Characters read: " + count);
    }
}