public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Error: Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            for (int i = 2; i < args.length; i++) {
                if (index >= 0 && index < args.length - 1) {
                    System.out.println(args[index]);
                } else {
                    System.out.println("Error: Index out of bounds.");
                }
            }
        } catch (NumberFormatException e) {
            System.out.println("Error: The second argument must be a valid integer.");
        }
    }
}