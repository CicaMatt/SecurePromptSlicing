import java.util.*;

public class Solution {
    public static int getValueFromArray(int[] arr,int index){
        if(index>=arr.length) 
            return -1;
        else    
            return arr[index];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int id_sequence[] = {1,2,3,4};
        System.out.print("Enter the index : ");
        int index = sc.nextInt();
        int result = getValueFromArray(id_sequence,index);
        System.exit(result);
    }
}