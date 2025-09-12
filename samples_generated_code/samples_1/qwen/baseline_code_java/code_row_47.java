import java.util.Scanner;

public class AddThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int number = scanner.nextInt();
        int result = number + 1000;
        System.out.println("Result: " + result);
        scanner.close();
    }
}