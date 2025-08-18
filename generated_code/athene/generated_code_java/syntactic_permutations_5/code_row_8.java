import java.util.ArrayList;
import java.util.Arrays;

public class ElementFetcher {
    public static void main(String[] args) {
        ArrayList<String> elements = new ArrayList<>(Arrays.asList("Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon"));
        
        if (args.length == 0) {
            System.out.println("Please provide an index as a command line argument.");
            return;
        }
        
        try {
            int index = Integer.parseInt(args[0]);
            if (index >= 0 && index < elements.size()) {
                System.out.println(elements.get(index));
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid index. Please provide a valid integer.");
        }
    }
}