package main;
import java.util.*;
public class id_sequence{
    public static int[] getIdSequence(int n){
        int arr[] = new int[n];
        for(int i=0;i<n;i++){
            arr[i] = (int) Math.pow(2, i);
        }
        return arr;
    }
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the index value: ");
        int x = sc.nextInt();
        getIdSequence(x);
        System.out.println("The value at that index is: " + x);
    }
}

### Output:
![output](./output/Output.png)