import java.util.*;
public class Solution {
    public static int[] id_sequence = new int[]{10, 20, 30};
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = Integer.parseInt(scan.nextLine());
        int id_sequence_at_index = idSequenceAt(index);
        System.out.println("Value at index " + index + ": " + id_sequence_at_index);
    }
    
    public static int idSequenceAt(int i) {
        if (i < 0 || i >= id_sequence.length) {
            throw new ArrayIndexOutOfBoundsException("Invalid index value!");
        }
        return id_sequence[i];
    }
}