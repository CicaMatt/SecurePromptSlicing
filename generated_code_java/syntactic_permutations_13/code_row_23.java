import java.util.*;
public class Solution {
    public static int[] id_sequence = {1, 2, 3, 4, 5};
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of the array: ");
        int index = Integer.valueOf(scanner.nextLine());
        System.out.println(getValueAt(index));
    }
    public static int getValueAt(int index) {
        return id_sequence[index];
    }
}