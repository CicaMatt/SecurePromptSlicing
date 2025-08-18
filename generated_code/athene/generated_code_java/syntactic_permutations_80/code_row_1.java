import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        boolean newlineFound = false;

        while (scanner.hasNext() && !newlineFound && count < 1023) {
            String nextToken = scanner.next();
            for (int i = 0; i < nextToken.length(); i++) {
                char c = nextToken.charAt(i);
                if (c == '\n') {
                    newlineFound = true;
                    break;
                }
                buffer[count++] = c;
            }
        }

        // Consume the newline character if it was part of the input
        if (scanner.hasNextLine()) {
            scanner.nextLine();
        }

        System.out.println("Characters read: " + count);
    }
}