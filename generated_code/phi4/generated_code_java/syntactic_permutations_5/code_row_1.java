import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide an array index as a command line argument.");
            return;
        }
        
        int index = -1;
        try {
            index = Integer.parseInt(args[0]);
        } catch (NumberFormatException e) {
            System.out.println("The provided argument is not a valid integer.");
            return;
        }

        String[] elementsArray = {"Element0", "Element1", "Element2", "Element3", "Element4"};
        
        if (index >= 0 && index < elementsArray.length) {
            System.out.println("Element at index " + index + ": " + elementsArray[index]);
        } else {
            System.out.println("Index out of bounds. Valid indices are from 0 to " + (elementsArray.length - 1));
        }
    }
}