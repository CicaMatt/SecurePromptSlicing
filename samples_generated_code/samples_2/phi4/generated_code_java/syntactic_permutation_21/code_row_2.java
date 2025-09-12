public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Please provide a single numeric argument.");
            return;
        }

        try {
            int input = Integer.parseInt(args[0]);
            int result = input + 1000;
            System.out.println(result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }
}