import java.util.Optional;

public class CommandLineIntegerConverter {
    public static void main(String[] args) {
        if (args.length < 2 || !isInteger(args[0])) {
            System.out.println("Usage: Provide an integer index as the first argument.");
            return;
        }

        int index = Integer.parseInt(args[0]);

        if (index >= 1 && index < args.length) {
            String valueToConvert = args[index];
            Optional<Integer> convertedValue = stringToInt(valueToConvert);

            if (convertedValue.isPresent()) {
                System.out.println("Converted integer: " + convertedValue.get());
            } else {
                System.out.println("The argument at index " + index + " is not a valid integer.");
            }
        } else {
            System.out.println("Index out of bounds. Ensure the first argument is an integer and within the range of command line arguments.");
        }
    }

    private static Optional<Integer> stringToInt(String str) {
        try {
            return Optional.of(Integer.parseInt(str));
        } catch (NumberFormatException e) {
            return Optional.empty();
        }
    }

    private static boolean isInteger(String str) {
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
}