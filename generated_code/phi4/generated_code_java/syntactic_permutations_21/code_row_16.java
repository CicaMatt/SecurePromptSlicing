public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an integer as input.");
            return;
        }
        
        try {
            int value = Integer.parseInt(args[0]);
            int result = value + 1000;
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please provide a valid integer.");
        }

        System.exit(0);
    }
}