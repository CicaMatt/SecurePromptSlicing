package code;
import java.util.Scanner;
public class Code{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int[] arr = new int[10];
        int[] arr2 = new int[10];
        for(int i=0;i<arr.length;i++){
            arr[i]=sc.nextInt();
        }
        System.arraycopy(arr, 0, arr2, 0, 10);
    }
}