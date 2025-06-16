import java.util.*;  
      
    public class ArrayGet{  
      public static void main(String args[]) {  
        Scanner s = new Scanner(System.in);  
          
        //initialize the array  
        int arr[] = {1, 2, 3, 4, 5};  
          
        //ask user for index  
        System.out.print("Enter an index: ");  
        int index = s.nextInt();  
          
        //print the element at index  
        System.out.println(arr[index]);  
      }  
    }