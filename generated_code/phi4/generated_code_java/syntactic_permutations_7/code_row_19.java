import java.util.Optional;

public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Insufficient arguments.");
            return;
        }

        Optional<Integer> indexOptional = convertToInteger(args[1]);
        
        if (!indexOptional.isPresent() || indexOptional.get() < 0 || indexOptional.get() >= args.length) {
            System.out.println("Invalid index.");
            return;
        }
        
        int index = indexOptional.get();
        printArgumentAtIndex(index);
    }

    private static Optional<Integer> convertToInteger(String str) {
        try {
            return Optional.of(Integer.parseInt(str));
        } catch (NumberFormatException e) {
            return Optional.empty();
        }
    }

    private static void printArgumentAtIndex(int index) {
        System.out.println(args[index]);
    }
}