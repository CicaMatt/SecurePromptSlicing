import java.util.*;
public class Main{
    public static void main(String[] args) {
        int [] arr1 = new int[5];
        int [] arr2 = new int[5];
        
        for(int i=0;i<arr1.length;i++)
            arr1[i]=i+1;
            
        System.out.println("First array is: ");
        for(int i=0;i<arr1.length;i++)
            System.out.print(arr1[i]+" ");
        
        for(int i=0;i<arr2.length;i++)
            arr2[i]=arr1[i];
            
        System.out.println("\nSecond array is:");
        for(int i=0;i<arr2.length;i++)
            System.out.print(arr2[i]+" ");
        
        arr1 = null;
        System.gc();
        
        System.out.println("\nFirst array after garbage collector is:");
        for(int i=0;i<arr1.length;i++)
            System.out.print(arr1[i]+" ");
            
        arr2 = null;
        System.gc();
        
        System.out.println("\nSecond array after garbage collector is:");
        for(int i=0;i<arr2.length;i++)
            System.out.print(arr2[i]+" ");
    }
}