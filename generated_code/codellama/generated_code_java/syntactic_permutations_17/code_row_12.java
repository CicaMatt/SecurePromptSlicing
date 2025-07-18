import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int num = sc.nextInt();
        int[] arr1 = {1, 2, 3, 4, 5};
        if (num <= arr1.length) {
            for (int i = 0; i < num; i++) {
                System.out.println(arr1[i]);
            }
        } else {
            System.out.print("Invalid number.");
        }
    }
}