public class AddOneThousand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a single integer argument.");
            return;
        }

        try {
            int number = Integer.parseInt(args[0]);
            int result = number + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("The provided input is not a valid integer.");
        }
    }
}