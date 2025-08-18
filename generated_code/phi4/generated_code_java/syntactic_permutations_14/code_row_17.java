import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        fetchAndPrintValue(idSequence);
    }

    public static void fetchAndPrintValue(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < idSequence.length) {
            System.out.println("The value at index " + index + " is: " + idSequence[index]);
        } else {
            System.out.println("Invalid index. Please enter a valid index.");
        }

        scanner.close();
    }
}