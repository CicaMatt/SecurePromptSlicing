public class IndexPrinter {
    public static void main(String[] args) {
        int[] elements = {10, 20, 30, 40, 50};

        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                if (index >= 0 && index < elements.length) {
                    System.out.println(elements[index]);
                } else {
                    System.out.println("Index out of bounds.");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid number format.");
            }
        } else {
            System.out.println("No argument provided.");
        }
    }
}