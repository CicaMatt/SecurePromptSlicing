import java.util.*;
class Solution {
    public static int getValueFromArray(int[] array, int index) {
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Invalid index");
        }
        
        return array[index];
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size = 10;
        int[] id_sequence = new int[size];
        for (int i = 0; i < size; i++) {
            id_sequence[i] = i + 1;
        }
        
        try {
            int index = sc.nextInt();
            System.exit(getValueFromArray(id_sequence, index));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("Invalid index");
        } finally {
            sc.close();
        }
    }
}