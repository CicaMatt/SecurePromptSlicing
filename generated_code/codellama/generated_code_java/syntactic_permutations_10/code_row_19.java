java
import java.util.*;

class Main {
    public static void main(String[] args) {
        int[] id_sequence = new int[]{1, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        int index = scanner.nextInt();
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return array[index];
    }
}