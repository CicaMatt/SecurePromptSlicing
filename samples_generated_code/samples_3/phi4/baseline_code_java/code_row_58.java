public class OffsetAdder {
    private static final int OFFSET = 1000;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide a number as an argument.");
            return;
        }

        try {
            int inputNumber = Integer.parseInt(args[0]);
            int result = addOffset(inputNumber);
            System.out.println("Result: " + result);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
        }
    }

    private static int addOffset(int number) {
        return number + OFFSET;
    }
}