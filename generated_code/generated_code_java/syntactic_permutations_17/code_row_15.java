import java.util.Scanner;

public class Index {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a number:");
        int idx = sc.nextInt();
        String[] arr = {"apple", "ball", "cat", "dog", "elephant"};
        System.out.println(arr[idx]);
    }
}