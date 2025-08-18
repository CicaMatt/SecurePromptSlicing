import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int input = scanner.nextInt();
        int result = input + 1000;
        System.out.println("Result: " + result);
        scanner.close();
    }
}