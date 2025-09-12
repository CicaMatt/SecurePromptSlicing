public class CommandLineIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java CommandLineIndex <index>");
            return;
        }

        String[] elements = {"Element0", "Element1", "Element2", "Element3", "Element4"};
        
        try {
            int index = Integer.parseInt(args[1]);
            if (index >= 0 && index < elements.length) {
                System.out.println(elements[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid number format for index.");
        }
    }
}