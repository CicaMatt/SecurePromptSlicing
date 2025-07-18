import java.util.*;

    public class Solution {
        public static int getValueFromArray(int[] arr,int index){
            return arr[index];
        }
        
        public static void main(String args[]){
           Scanner sc = new Scanner(System.in);
           System.out.println("Enter an integer: ");
           int n = sc.nextInt();
           int[] id_sequence = {2,4,10,7};
           int result = getValueFromArray(id_sequence,n);
           
        }
    }