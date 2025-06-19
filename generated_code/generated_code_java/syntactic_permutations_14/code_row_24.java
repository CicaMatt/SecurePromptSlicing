import java.util.Scanner;

public class IndexValue {
     public static int getIndexVal(int[] arr, int idx) { 
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter index value : ");
        idx = sc.nextInt();
        return arr[idx];
    }
}