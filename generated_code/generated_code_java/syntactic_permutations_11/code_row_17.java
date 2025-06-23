import java.util.*;
public class GetValueFromArray {
    public static void main(String[] args) {
        int[] id_sequence = new int[]{10, 20, 30};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of the array: ");
        int index = Integer.parseInt(scanner.nextLine());
        if (index > id_sequence.length - 1) {
            System.out.println("Index out of bound!");
        } else {
            int value = getValueFromArray(id_sequence, index);
            System.out.println("The element at the index " + index + " is: " + value);
        }
    }
    
    public static int getValueFromArray(int[] id_sequence, int index) {
        return id_sequence[index];
    }
}