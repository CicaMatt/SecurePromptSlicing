java 
import java.util.*;
public class Array_Index {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index value : ");
        int n = sc.nextInt();
        int arr[] = {10, 20, 30, 40, 50};

        if (n > 4 || n < 0) {
            System.out.println("Invalid index value");
        } else {
            System.out.println(arr[n]);
        }
    }
}