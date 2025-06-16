import java.util.Arrays;

public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index you want to find its value in id_sequence: ");
        int n = sc.nextInt();
        
        // Array of string values
        String id_sequence[] = {"a", "b", "c"};
        
        // Printing the value at that index
        System.out.println("Value at index " + n + " is: " + getIndex(id_sequence, n));
    }
    
    public static String getIndex(String[] arr, int index) {
        return arr[index];
    }
}