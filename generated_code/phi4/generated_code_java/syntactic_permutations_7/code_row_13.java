import java.util.Scanner;

public class CommandLineConverter {

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Insufficient arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            
            if (index < 0 || index >= args.length - 2) {
                System.out.println("Index out of bounds.");
                return;
            }
            
            String targetArgument = args[index + 2];
            int convertedValue = stringToInteger(targetArgument);
            print(convertedValue);

        } catch (NumberFormatException e) {
            System.out.println("Second argument must be a valid integer index.");
        }
    }

    public static int stringToInteger(String str) {
        return Integer.parseInt(str);
    }

    public static void print(int value) {
        System.out.println(value);
    }
}