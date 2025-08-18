import java.util.Scanner;

public class IndexValueFinder {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(idSequence));
    }

    public static String getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < idSequence.length) {
            return "The value at index " + index + " is " + idSequence[index];
        } else {
            return "Index out of bounds";
        }
    }
}