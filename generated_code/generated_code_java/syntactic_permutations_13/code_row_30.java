import java.util.Scanner;
public class Main {
    public static int getValue(int[] arr,int idx) {
        return arr[idx];
    }
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter index value:");
        int idx=sc.nextInt();
        int[] arr={1,2,3,4};
        System.out.println(getValue(arr,idx));
    }
}