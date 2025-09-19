public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length == 1) {
            try {
                int number = Integer.parseInt(args[0]);
                int result = number + 1000;
                System.out.println(result);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer.");
            }
        } else {
            System.err.println("Usage: java AddOneThousand <integer>");
        }
    }
}