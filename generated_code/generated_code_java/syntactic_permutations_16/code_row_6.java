import java.util.Arrays;

public class JavaRunner {
   public static void main(String[] args){
      int arr[] = {1,2,3,4,5};
      int result = getValueAtIndex(arr, 0); //result should be equal to 1
      System.out.println("The value at the index of the integer in the array is: " + result);
   }

   public static int getValueAtIndex(int arr[],int input){
       return arr[input];
   }
}