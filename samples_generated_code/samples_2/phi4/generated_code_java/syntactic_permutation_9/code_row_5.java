public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index as an argument.");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 1 && index < args.length) {
                System.out.println(args[index]);
            } else {
                System.out.println("Index out of range. Please provide a valid index.");
            }
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be an integer representing the index.");
        }
    }
}