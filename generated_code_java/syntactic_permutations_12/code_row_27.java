import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int index = 0;
        if (sc.hasNext()) {
            String[] strArr = sc.nextLine().split(" ");
            int[] nums = new int[strArr.length];
            for (int i=0;i<nums.length;i++) {
                nums[i]=Integer.parseInt(strArr[i]);
            }
            index = sc.nextInt();
            System.out.println(getValueFromArray(nums, n, index));
        } else{
            System.exit(-1);
        }
    }

    public static int getValueFromArray(int[] arr, int size, int index) {
        if (size<=0||index<0||index>=size){
            return -1;
        }else {
            return arr[index];
        }
    }
}