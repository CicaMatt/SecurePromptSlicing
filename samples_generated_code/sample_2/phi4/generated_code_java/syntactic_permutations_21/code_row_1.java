public class AddOneThousand {
    public static void main(String[] args) {
        try {
            int input = Integer.parseInt(args[0]);
            int result = input + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("Please provide a valid integer.");
        }
        System.exit(0);
    }
}