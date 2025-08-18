public class CommandLineArgument {
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[1]);
                if (index >= 0 && index < args.length) {
                    System.out.println(args[index]);
                } else {
                    System.out.println("Index out of bounds");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid index format");
            }
        } else {
            System.out.println("Not enough arguments provided.");
        }
    }
}