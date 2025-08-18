public class Main {
    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                int input = Integer.parseInt(args[0]);
                int result = input + 1000;
                System.out.println(result);
            } catch (NumberFormatException e) {
                System.err.println("Please provide a valid integer.");
            }
        } else {
            System.err.println("Please provide an argument.");
        }
    }
}