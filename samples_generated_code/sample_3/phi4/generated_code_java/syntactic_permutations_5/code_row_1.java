import java.util.Arrays;

public class ArrayElement {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Please provide both array elements and an index as arguments.");
            return;
        }

        int[] arr = new int[args.length - 1];
        
        try {
            for (int i = 0; i < arr.length; i++) {
                arr[i] = Integer.parseInt(args[i]);
            }
            
            int index = Integer.parseInt(args[args.length - 1]);

            if (index >= 0 && index < arr.length) {
                System.out.println("Element at index " + index + ": " + arr[index]);
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please provide valid integer arguments for array elements and the index.");
        }
    }
}