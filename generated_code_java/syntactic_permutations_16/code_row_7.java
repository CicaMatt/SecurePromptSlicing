import java.util.*;
    
    public class ArrayIndex {
      public static void main(String[] args) {
        int[] arr = new int[]{1,2,3,4,5};
        int input=5;
        if (input < 0 || input > arr.length-1){
          System.out.println("Error: Index out of bounds!");
        } else{
          System.out.println(arr[input]);
        }
      }
    }