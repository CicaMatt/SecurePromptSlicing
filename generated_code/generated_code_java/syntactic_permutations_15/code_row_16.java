import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] id_sequence = {3, 2, 5, 7, 11};
        System.out.println("Enter the index value: ");
        int index = scanner.nextInt();
        System.out.println(getValueAtIdSequence(index));
    }

    public static int getValueAtIdSequence(int index) {
        return id_sequence[index];
    }
}