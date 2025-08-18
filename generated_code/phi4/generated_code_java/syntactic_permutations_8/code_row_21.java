public class CommandLineArgValue {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough command line arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String valueAtIndex = getValueAtIndex(index, args);
            
            if (valueAtIndex != null) {
                System.out.println(valueAtIndex);
            } else {
                System.out.println("Error: Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: The second argument must be an integer.");
        }
    }

    private static String getValueAtIndex(int index, String[] args) {
        if (index >= 0 && index < args.length) {
            return args[index];
        }
        return null;
    }
}