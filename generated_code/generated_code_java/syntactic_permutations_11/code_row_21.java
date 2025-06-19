import java.util.*;

class GetValueFromArray {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] id_sequence = {1, 2, 3};
        System.exit(getValueFromArray(id_sequence, id_sequence.length, sc.nextInt()));
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < size) {
            return arr[index];
        } else {
            throw new ArrayIndexOutOfBoundsException();
        }
    }
}