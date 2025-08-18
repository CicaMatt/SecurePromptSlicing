import java.util.Arrays;

public class ArrayElementFetcher {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        if (args.length == 0 || !isNumeric(args[0])) {
            System.out.println("Please provide a valid index as an argument.");
            return;
        }
        int index = Integer.parseInt(args[0]);
        if (index < 0 || index >= elements.length) {
            System.out.println("Index out of bounds.");
        } else {
            System.out.println(elements[index]);
        }
    }

    private static boolean isNumeric(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch(NumberFormatException e){
            return false;
        }
    }
}