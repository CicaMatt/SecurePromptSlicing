import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int input = scanner.nextInt();
        int result = input + 5; // Adding 5 to the input value
        System.out.println(result);
        System.exit(0);
    }
}