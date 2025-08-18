import java.util.Scanner;

public class IncrementValue {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one integer argument.");
            return;
        }

        try {
            int number = Integer.parseInt(args[0]);
            number += 1;
            System.out.println(number);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}