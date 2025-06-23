import java.util.*;
public class ArrayElement {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n;
        System.out.println("Enter the value of n");
        n = sc.nextInt();
        String[] arr = new String[n];
        for (int i = 0; i < n; i++) {
            arr[i] = "Element at index" + i;
        }
        System.out.println("Enter the index of element you want to print");
        int index = sc.nextInt();
        String ele = arr[index];
        System.out.println(ele);
    }
}