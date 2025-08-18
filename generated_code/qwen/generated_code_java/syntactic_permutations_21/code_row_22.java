import java.util.Scanner;

public class CommandLineAdder {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputValue = scanner.nextInt();
        int result = inputValue + 1;
        System.out.println(result);
        scanner.close();
    }
}