public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Not enough arguments provided.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String value = args[index];
            System.out.println(value);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds. Please provide a valid index.");
        }
    }
}