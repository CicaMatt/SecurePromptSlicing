import java.util.*;
public class Solution {
    static int[] id_sequences = new int[]{1, 2, 3};
    public static void main(String args[]){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the index you want to access from the array");
        int index = scanner.nextInt();
        System.out.println("The value at that particular index is "+getValueAt(index));
    }
    public static int getValueAt(int index){
        return id_sequences[index];
    }
}