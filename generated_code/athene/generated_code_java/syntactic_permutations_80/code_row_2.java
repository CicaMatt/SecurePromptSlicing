import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = scanner.useDelimiter("\n").next().getChars(0, 1023, buffer, 0);
        System.out.println("Characters read: " + (charsRead > 1023 ? 1023 : charsRead));
    }
}