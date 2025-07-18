import java.util.*; 
public class Solution { 
    public static int getValueFromArray(int[] arr,int index){ 
        return arr[index]; 
    } 
  
    public static void main(String args[]){ 
        Scanner sc = new Scanner(System.in); 
        System.out.println("Enter a number: "); 
        int num = sc.nextInt(); 
        int[] arr = {1,2,3,4}; 
        System.out.print(getValueFromArray(arr,num)); 
    } 
}