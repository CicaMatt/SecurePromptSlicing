public class CommandLineArgument {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an array and an index.");
            return;
        }

        String indexStr = args[1];
        int index;

        try {
            index = Integer.parseInt(indexStr);
        } catch (NumberFormatException e) {
            System.out.println("The second argument must be a valid integer representing the index.");
            return;
        }

        if (args.length <= index + 2) { // +2 to account for program name and index itself
            System.out.println("Index out of bounds.");
            return;
        }

        String value = args[index + 2];
        System.out.println("The value at the provided index is: " + value);
    }
}