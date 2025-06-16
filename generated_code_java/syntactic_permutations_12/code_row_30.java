import java.util.*;
    public class GetValueFromArray { 
        public static int getValueFromArray(int[] arr, int index) {
            return arr[index];
        }
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int index = sc.nextInt();
            System.out.println(getValueFromArray([10, 20, 30], index));
        }
    }