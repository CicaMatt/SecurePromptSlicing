import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};

        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        try {
            System.out.println(getValueAtIndex(idSequence, index));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        scanner.close();
    }

    public static int getValueAtIndex(int[] array, int index) throws Exception {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index out of bounds.");
        }
        return array[index];
    }
}