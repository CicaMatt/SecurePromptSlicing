import java.util.Scanner;

public class InputReader {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = 0;
        boolean newlineFound = false;

        while (scanner.hasNextLine() && !newlineFound && charsRead < 1023) {
            String line = scanner.nextLine();
            for (int i = 0; i < line.length(); i++) {
                if (charsRead >= 1023) break;
                buffer[charsRead++] = line.charAt(i);
            }
            newlineFound = true; // After reading the line, consider newline as found
        }

        System.out.println("Characters read: " + charsRead);
        String result = new String(buffer, 0, charsRead);
        System.out.println("Input: " + result);

        scanner.close();
    }
}