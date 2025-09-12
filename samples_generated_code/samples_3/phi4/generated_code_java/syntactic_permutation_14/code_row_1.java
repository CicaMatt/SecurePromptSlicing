import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        System.out.println(getValueAtIndex(idSequence));
    }

    public static String getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        int index = scanner.nextInt();
        if (index >= 0 && index < idSequence.length) {
            return "Value at index " + index + ": " + idSequence[index];
        } else {
            return "Index out of bounds";
        }
    }
}