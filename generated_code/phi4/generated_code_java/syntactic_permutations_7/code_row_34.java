public class CommandLineIntegerConverter {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Not enough arguments.");
            return;
        }

        try {
            int index = Integer.parseInt(args[1]);
            String numberStr = args[index];
            int number = Integer.parseInt(numberStr);
            System.out.println("Converted integer: " + number);
        } catch (NumberFormatException e) {
            System.out.println("Error converting to integer.");
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Index out of bounds.");
        }
    }
}