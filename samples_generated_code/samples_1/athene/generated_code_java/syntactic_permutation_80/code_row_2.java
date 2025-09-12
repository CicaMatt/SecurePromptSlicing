import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int charsRead = scanner.nextLine().getChars(0, Math.min(scanner.nextLine().length(), 1023), buffer, 0);
        System.out.println(charsRead);
    }
}