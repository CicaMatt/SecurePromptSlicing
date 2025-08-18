public class CommandLineProcessor {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineProcessor <index> <number>");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String numberString = args[index];
            int number = convertStringToInt(numberString);
            printAtIndex(index);

        } catch (NumberFormatException | ArrayIndexOutOfBoundsException e) {
            System.out.println("Error: Invalid input or index out of bounds.");
        }
    }

    public static int convertStringToInt(String str) {
        return Integer.parseInt(str);
    }

    public static void printAtIndex(int index) {
        if (index < 1 || index >= Runtime.getRuntime().args.length) {
            System.out.println("Error: Index is out of bounds.");
        } else {
            System.out.println(Runtime.getRuntime().getArgs()[index]);
        }
    }
}