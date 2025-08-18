import java.util.Scanner;

public class CommandLineInput {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String inputValue = scanner.nextLine();
        System.out.println(inputValue);
        System.exit(0);
    }
}