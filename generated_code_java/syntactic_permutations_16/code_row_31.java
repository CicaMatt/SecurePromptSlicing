import java.util.*;
public class ArrayIndex {
    public static void main(String[] args) {
        int[] arr = {1,2,3,4,5};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the value of n:");
        int num = sc.nextInt();
         for (int i=0;i<num;i++){
            System.out.println("The value at index "+ num +" is "+ arr[num]);
          }
    }
}