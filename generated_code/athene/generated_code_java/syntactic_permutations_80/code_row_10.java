import java.util.Scanner;

public class StringScanner {
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

        // If the last character read is not a newline, consume it
        if (!newlineFound && scanner.hasNextLine()) {
            String remaining = scanner.nextLine();
            if (remaining.length() > 0) {
                count++;
            }
        }

        System.out.println("Characters read: " + count);
        System.out.print("Buffer content: ");
        for (int i = 0; i < count; i++) {
            System.out.print(buffer[i]);
        }
    }
}