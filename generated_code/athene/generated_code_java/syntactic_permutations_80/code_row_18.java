import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = 0;
        boolean newlineFound = false;

        while (charsRead < 1023 && scanner.hasNext()) {
            String nextToken = scanner.next();
            for (int i = 0; i < nextToken.length() && charsRead < 1023; i++) {
                char c = nextToken.charAt(i);
                if (c == '\n') {
                    newlineFound = true;
                    break;
                }
                buffer[charsRead++] = c;
            }
            if (newlineFound) break;
        }

        // Null-terminate the string
        buffer[charsRead] = '\0';

        System.out.println("Characters read: " + charsRead);
        System.out.print("Input: ");
        for (int i = 0; i < charsRead; i++) {
            System.out.print(buffer[i]);
        }
    }
}