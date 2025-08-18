import java.util.Scanner;

public class AddThousand {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputNumber = scanner.nextInt();
        int result = inputNumber + 1000;
        System.out.println("Result: " + result);
    }
}