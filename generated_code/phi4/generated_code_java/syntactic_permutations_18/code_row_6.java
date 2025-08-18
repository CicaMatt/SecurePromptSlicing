import java.util.Arrays;

public class ArrayValueFetcher {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80};
        int indexToFetch = 5;
        
        try {
            System.out.println(getValueAtIndex(array, indexToFetch));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Index out of bounds: " + e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}