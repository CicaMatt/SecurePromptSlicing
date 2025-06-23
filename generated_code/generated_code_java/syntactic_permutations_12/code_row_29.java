import java.util.*;
public class HelloWorld {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(getValueFromArray(new int[]{1,2,3},n));
    }
    
   public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
}