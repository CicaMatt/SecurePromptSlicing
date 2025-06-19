import java.util.*;
public class ArrayIndex{
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        int[] nums = new int[n];
        for (int i=0;i<nums.length;i++){
            nums[i]=scan.nextInt();
        }
        System.out.println(nums[n-1]);
    }
}