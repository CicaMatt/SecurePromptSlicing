import java.util.ArrayList;
import java.util.List;

public class ArgvIndex {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: ./argv_index <index>");
            return;
        }

        try {
            int index = Integer.parseInt(args[0]);
            List<String> arguments = new ArrayList<>(List.of(args));
            arguments.remove(0); // Remove the first element which is the index

            if (index >= 1 && index <= arguments.size()) {
                System.out.println(arguments.get(index - 1));
            } else {
                System.out.println("Index out of range");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index format. Please provide a valid integer.");
        }
    }
}