import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (size == 0 || index < 0 || index >= size) return 0;
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a valid number: ");
        
        int n = scanner.nextInt();
        int[] id_sequence = {1, 2, 3, 4};
        
        System.out.println(getValueFromArray(id_sequence, id_sequence.length, n));
    }
}