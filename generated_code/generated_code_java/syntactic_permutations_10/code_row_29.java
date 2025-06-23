import java.util.*;
public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.exit(getValueFromArray(id_sequence, id_sequence.length, n));
    }
    public static int getValueFromArray(int array[], int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1;
    }
}