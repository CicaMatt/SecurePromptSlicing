public class Main {
    public static void main(String[] args) {
        if (args.length > 1) {
            try {
                int index = Integer.parseInt(args[1]);
                System.out.println(args[index]);
            } catch (NumberFormatException | ArrayIndexOutOfBoundsException e) {
                System.err.println("Invalid input. Please provide a valid integer index.");
            }
        } else {
            System.err.println("Please provide at least two arguments.");
        }
    }
}