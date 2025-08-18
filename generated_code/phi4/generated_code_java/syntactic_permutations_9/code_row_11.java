public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            String argumentToPrint = args[index];
            System.out.println(argumentToPrint);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be a valid integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Argument index out of bounds.");
        }
    }
}