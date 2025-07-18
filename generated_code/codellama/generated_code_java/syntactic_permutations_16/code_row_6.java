import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            int[] nums = new int[5];
            System.out.println("Enter 5 values into an array: ");
            Scanner scanner = new Scanner(System.in);
            for (int i = 0; i < 5; i++) {
                nums[i] = scanner.nextInt();
            }
    
            System.out.println("Enter the index of the value you want to retrieve: ");
            int idx = scanner.nextInt();
            if (idx >= 0 && idx < 5) {
                System.out.println(nums[idx]);
            } else {
                System.out.println("Invalid index");
            }
        }
    }