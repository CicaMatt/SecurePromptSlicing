import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {0, 1, 2, 3};
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        return arr[index];
    }
}