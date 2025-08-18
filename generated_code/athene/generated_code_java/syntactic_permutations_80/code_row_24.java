import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        String input;
        
        if (scanner.hasNextLine()) {
            input = scanner.nextLine();
            int length = Math.min(input.length(), 1023);
            for (int i = 0; i < length; i++) {
                buffer[i] = input.charAt(i);
            }
            System.out.println("Number of characters read: " + length);
        } else {
            System.out.println("No input was provided.");
        }

        scanner.close();
    }
}