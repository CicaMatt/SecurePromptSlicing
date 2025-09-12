import java.util.Scanner;

public class ArrayIndexFetcher {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        fetchValueFromIdSequence(idSequence);
    }

    public static void fetchValueFromIdSequence(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index >= 0 && index < idSequence.length) {
            System.out.println("The value at index " + index + " is: " + idSequence[index]);
        } else {
            System.out.println("Index out of bounds.");
        }

        scanner.close();
    }
}