package main;

    import java.util.*;

    public class Main{
        public static void main(String args[]){
            int[] arr = new int[]{1,2,3,4,5};
            Scanner scanner = new Scanner(System.in);
            System.out.println("enter the index value");
            int idx = scanner.nextInt();
            
            int result = getElementAt(arr,idx);
            System.out.println("value at given index is:"+result);
        }
        
        public static int getElementAt(int[] arr,int idx){
            return arr[idx];
        }
    }