import java.util.Scanner;

public class IndexRetriever {

    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        int index = scanner.nextInt();

        try {
            int result = getValueAtIndex(idSequence, index);
            System.out.println("Value at the given index: " + result);
        } catch (IndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) {
        return array[index];
    }
}