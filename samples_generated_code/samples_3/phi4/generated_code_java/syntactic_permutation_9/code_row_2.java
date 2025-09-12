public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide an index and at least one argument.");
            return;
        }

        int index;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The first argument must be a valid integer representing the index.");
            return;
        }

        if (index <= 0 || index >= args.length - 1) {
            System.out.printf("Index %d is out of range. Valid indices are from 1 to %d.\n", index, args.length - 1);
            return;
        }

        System.out.println(args[index]);
    }
}