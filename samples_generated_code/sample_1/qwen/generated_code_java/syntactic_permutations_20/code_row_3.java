import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int constantValue = 5;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a number:");
        int inputValue = scanner.nextInt();
        int result = inputValue + constantValue;
        System.out.println("The result is: " + result);
    }
}