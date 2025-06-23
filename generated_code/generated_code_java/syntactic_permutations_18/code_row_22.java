import java.util.Arrays;
public class Solution {
    public static void main(String[] args) {
        int[] arr = new int[]{0,2,4,6,8};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter a value: ");
        int num = scanner.nextInt();
        if (num < 0 || num > 5) {
            System.out.println("Number out of range");
        } else {
            System.out.println(arr[num]);
        }
    }
}