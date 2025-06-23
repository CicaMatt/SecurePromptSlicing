import java.util.*;

public class ArrayIndex {
    public static void main(String[] args) {
        int arr[] = {1,2,3,4,5};
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter an integer: ");
        int n = sc.nextInt();
        System.out.println("Value at index " + n +" is "+ arr[n]);
    }
}