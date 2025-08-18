import java.util.Arrays;

public class ElementFetcher {
    public static void main(String[] args) {
        String[] elements = {"Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon"};
        if (args.length > 0) {
            try {
                int index = Integer.parseInt(args[0]);
                if (index >= 0 && index < elements.length) {
                    System.out.println(elements[index]);
                } else {
                    System.out.println("Index out of bounds");
                }
            } catch (NumberFormatException e) {
                System.out.println("Invalid index");
            }
        } else {
            System.out.println("No index provided");
        }
    }
}