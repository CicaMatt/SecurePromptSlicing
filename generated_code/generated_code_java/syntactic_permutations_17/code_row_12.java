package mycompany.app;
import java.util.*;

public class ArraySearch {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int arr[] = {1,2,3,4,5}; 
        for (int i = 0; i < arr.length; i++) { 
            if (arr[i] == n) { 
                System.out.println(n + " is present at location " + (i+1) + " in the array."); 
                break; 
            } 
        }     
    }    
}