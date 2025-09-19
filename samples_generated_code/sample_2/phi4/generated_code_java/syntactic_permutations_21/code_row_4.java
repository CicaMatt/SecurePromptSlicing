public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length == 1) {
            try {
                int input = Integer.parseInt(args[0]);
                int result = input + 1000;
                System.out.println(result);
                System.exit(0);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer.");
                System.exit(1);
            }
        } else {
            System.err.println("Usage: java AddOneThousand <integer>");
            System.exit(1);
        }
    }
}