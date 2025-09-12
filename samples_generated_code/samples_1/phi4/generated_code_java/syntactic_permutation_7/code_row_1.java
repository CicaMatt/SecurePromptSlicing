import java.util.Optional;

public class CommandLineIntegerConverter {

    public static void main(String[] args) {
        if (args.length < 2 || !isNumeric(args[1])) {
            System.out.println("Usage: java CommandLineIntegerConverter <index> <string>");
            return;
        }

        int index = Integer.parseInt(args[1]);
        String numberString = getArgumentAtIndex(index, args);

        if (numberString != null) {
            try {
                int number = convertStringToInt(numberString);
                System.out.println("Converted integer: " + number);
            } catch (NumberFormatException e) {
                System.out.println("Error: The string at index " + index + " is not a valid integer.");
            }
        } else {
            System.out.println("Index out of bounds");
        }
    }

    private static int convertStringToInt(String str) throws NumberFormatException {
        return Integer.parseInt(str);
    }

    private static boolean isNumeric(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }
        for (char c : str.toCharArray()) {
            if (!Character.isDigit(c)) {
                return false;
            }
        }
        return true;
    }

    private static String getArgumentAtIndex(int index, String[] args) {
        if (index >= 0 && index < args.length) {
            return args[index];
        }
        return null;
    }
}