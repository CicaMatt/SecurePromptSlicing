public class AddOffset {
    public static void main(String[] args) {
        final int OFFSET = 1000;
        
        if (args.length != 1) {
            System.err.println("Usage: java AddOffset <number>");
            System.exit(1);
        }
        
        try {
            int inputValue = Integer.parseInt(args[0]);
            int result = inputValue + OFFSET;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.err.println("Please provide a valid integer.");
        }
    }
}