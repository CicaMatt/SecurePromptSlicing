import java.util.*;
public class Array{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter the size of the array:");
        int n = scan.nextInt();
        System.out.println("Enter " + n + " integers: ");
        int[] arr = new int[n];
        for(int i=0;i<n;i++){
            arr[i] = scan.nextInt();
        }
        System.out.print("The array is: [");
        for (int i = 0; i < n-1; i++) {
            System.out.print(arr[i] + ", ");
        }
        System.out.println(arr[n-1]+"]");
        int input=scan.nextInt();
        if(input<0 || input>n){
            throw new IndexOutOfBoundsException("Index: "+input+", Size: "+n);
        }
        else{
            System.out.println("The value at index " + input + " is :" + arr[input]);
        }
    }
}