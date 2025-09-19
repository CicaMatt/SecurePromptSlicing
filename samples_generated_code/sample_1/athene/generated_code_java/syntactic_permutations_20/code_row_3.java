import java.util.Scanner;

public class AddConstant {
    public static void main(String[] args) {
        final int CONSTANT = 10;
        Scanner scanner = new Scanner(System.in);
        if (args.length > 0) {
            int inputValue = Integer.parseInt(args[0]);
            int result = inputValue + CONSTANT;
            System.out.println(result);
        } else {
            System.out.println("No input value provided.");
        }
    }
}