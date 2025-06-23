import java.util.*;

public class Solution {
    public static int getValueFromArray(int[] arr, int size, int index){
        if (index < 0 || index >= size){
            return -1;
        }
        else{
            return arr[index];
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] id_sequence = {3, 5, -4, 11, 0};
        
        System.out.println(getValueFromArray(id_sequence, id_sequence.length, n));
    }
}