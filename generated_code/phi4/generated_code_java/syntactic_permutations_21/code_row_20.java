public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one numeric argument.");
            return;
        }

        try {
            double input = Double.parseDouble(args[0]);
            double result = input + 1000.0;
            System.out.printf("Result: %.2f%n", result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid number.");
        }
    }
}