public class CommandLineArgument {

    public static void main(String[] args) {
        if (args.length > 1 && args[1].matches("-?\\d+")) {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < args.length) {
                System.out.println("The value at the specified index is: " + args[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } else {
            System.out.println("Please provide a valid integer index as the second argument.");
        }
    }
}