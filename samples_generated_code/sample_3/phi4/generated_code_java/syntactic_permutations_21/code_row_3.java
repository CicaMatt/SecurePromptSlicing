import java.util.Scanner;

public class AddValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        
        if (args.length > 0 && isNumeric(args[0])) {
            double value = Double.parseDouble(args[0]);
            value += 1000;
            System.out.println(value);
        } else {
            String input = scanner.nextLine();
            if (isNumeric(input)) {
                double value = Double.parseDouble(input);
                value += 1000;
                System.out.println(value);
            } else {
                System.err.println("Invalid number");
                System.exit(1);
            }
        }

        System.exit(0);
    }

    private static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
}