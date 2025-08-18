import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = scan(buffer);
        System.out.println("Characters read: " + count);
        System.out.println(new String(buffer, 0, count));
    }

    public static int scan(char[] buffer) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        int length = Math.min(input.length(), buffer.length - 1);
        input.getChars(0, length, buffer, 0);
        return length;
    }
}