import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int value = Integer.parseInt(scanner.nextLine());
        int result = value + 1000;
        System.out.println(result);
        System.exit(0);
    }
}