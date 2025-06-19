import java.util.*;

public class Solution {
    static int[] id_sequence = new int[]{1, 2, 3, 4, 5};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        String input = scanner.nextLine();
        int index = Integer.parseInt(input);
        System.out.println("The value at the given index is " + getValue(index));
    }

    public static int getValue(int index) {
        return id_sequence[index];
    }
}