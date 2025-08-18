import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1023]; // 1023 to leave space for null terminator
        int charactersRead = 0;
        
        if (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            int length = Math.min(input.length(), buffer.length);
            for (int i = 0; i < length; i++) {
                buffer[i] = input.charAt(i);
                charactersRead++;
            }
        }

        System.out.println("Characters read: " + charactersRead);
    }
}