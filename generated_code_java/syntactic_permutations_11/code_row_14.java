import java.util.*;

public class Solution {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {1, 2, 3, 4, 5};
        System.out.println("Enter an index to get the value: ");
        int index = scanner.nextInt();
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        System.exit(value);
    }
}