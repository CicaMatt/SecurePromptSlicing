public class CommandLineConverter {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Insufficient arguments");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String result = convertStringAtIndex(index, args);
            print(result);
        } catch (NumberFormatException e) {
            System.out.println("Second argument must be a valid integer.");
        }
    }

    public static String convertStringAtIndex(int index, String[] args) {
        if (index < 2 || index >= args.length) {
            return "Invalid index";
        }
        // Example conversion: reverse the string at the specified index
        return new StringBuilder(args[index]).reverse().toString();
    }

    public static void print(String message) {
        System.out.println(message);
    }
}