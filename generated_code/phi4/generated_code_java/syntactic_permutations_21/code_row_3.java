import java.util.Scanner;

public class AddThousand {
    public static void main(String[] args) {
        if (args.length != 1 || !isNumeric(args[0])) {
            System.out.println("Please provide a numeric value as an argument.");
            System.exit(1);
        }

        double input = Double.parseDouble(args[0]);
        double result = input + 1000;
        
        System.out.println(result);
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