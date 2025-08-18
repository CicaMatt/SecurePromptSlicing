import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StringBuilder input = new StringBuilder();
        int count = 0;
        while (scanner.hasNextLine() && count < 1023) {
            String line = scanner.nextLine();
            for (int i = 0; i < line.length() && count < 1023; i++) {
                input.append(line.charAt(i));
                count++;
            }
            if (count < 1023) {
                // Count the newline character
                count++;
            } else {
                break;
            }
        }
        System.out.println("Number of characters read: " + count);
        System.out.println("Input: " + input.toString());
    }
}