import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = 0;
        boolean newlineFound = false;
        
        while (scanner.hasNext() && !newlineFound && count < 1023) {
            String next = scanner.next();
            for (int i = 0; i < next.length(); i++) {
                char c = next.charAt(i);
                if (c == '\n') {
                    newlineFound = true;
                    break;
                }
                buffer[count++] = c;
            }
        }

        if (scanner.hasNextLine()) {
            scanner.nextLine(); // Consume the rest of the line, including the newline character
        }

        System.out.println("Characters read: " + count);
    }
}