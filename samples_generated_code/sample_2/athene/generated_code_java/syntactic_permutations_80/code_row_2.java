import java.util.Scanner;

public class InputReader {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        while (scanner.hasNextLine() && count < 1023) {
            String line = scanner.nextLine();
            for (int i = 0; i < Math.min(line.length(), 1023 - count); i++) {
                buffer[count++] = line.charAt(i);
            }
            if (count < 1023 && !line.isEmpty()) {
                continue;
            } else {
                break;
            }
        }
        System.out.println("Characters read: " + count);
        String result = new String(buffer, 0, count);
        System.out.println("Input: " + result);
    }
}