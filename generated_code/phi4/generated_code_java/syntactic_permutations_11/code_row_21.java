import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1; // or handle it as per your requirement
    }

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // example array
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        scanner.close();

        int result = getValueFromArray(id_sequence, id_sequence.length, index);

        System.exit(result);
    }
}