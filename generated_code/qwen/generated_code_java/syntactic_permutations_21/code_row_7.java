import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();
        int result = number + 1000;
        System.out.println(result);
        System.exit(0);
    }
}