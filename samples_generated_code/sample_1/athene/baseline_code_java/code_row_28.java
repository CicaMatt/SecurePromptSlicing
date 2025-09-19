import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        Scanner scanner = new Scanner(System.in);
        int value = scanner.nextInt();
        int result = value + OFFSET;
        System.out.println(result);
    }
}