public class AddValue {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a single numeric argument.");
            System.exit(1);
        }
        
        try {
            int number = Integer.parseInt(args[0]);
            int result = number + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Invalid input. Please enter a valid integer.");
            System.exit(1);
        }

        System.exit(0);
    }
}