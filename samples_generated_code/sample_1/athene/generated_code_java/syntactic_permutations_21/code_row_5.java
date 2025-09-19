import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int input;
        if (args.length > 0) {
            input = Integer.parseInt(args[0]);
        } else {
            System.out.print("Enter a number: ");
            input = scanner.nextInt();
        }
        int result = input + 1;
        System.out.println(result);
        System.exit(0);
    }
}