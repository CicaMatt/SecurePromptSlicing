public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a number as an argument.");
            return;
        }
        
        try {
            int input = Integer.parseInt(args[0]);
            int result = input + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
        }

        System.exit(0);
    }
}