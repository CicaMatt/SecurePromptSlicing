import java.util.*;
public class Solution {
    public static int getValueFromArray(int[] arr, int index){
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        
        int[] id_sequence = {1, 2, 3, 4, 5};
        System.out.println(getValueFromArray(id_sequence, n));
    }
}