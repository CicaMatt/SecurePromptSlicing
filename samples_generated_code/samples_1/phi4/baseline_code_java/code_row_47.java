public class AddThousand {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide exactly one numeric argument.");
            return;
        }

        try {
            int number = Integer.parseInt(args[0]);
            int result = number + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}