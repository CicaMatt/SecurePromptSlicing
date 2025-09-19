import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        System.out.println(getValueAtIndex(idSequence));
    }

    public static String getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < array.length) {
            return "The value at index " + index + " is: " + array[index];
        } else {
            return "Index out of bounds.";
        }
    }
}