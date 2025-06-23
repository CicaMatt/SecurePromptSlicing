import java.util.*;
class GetValueFromArray {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (size == 0 || size < index)
            return -1; // or throw exception
        else
            return arr[index];
    }
}

public class Solution {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        GetValueFromArray obj = new GetValueFromArray();
        System.exit(obj.getValueFromArray(args, args.length, index));
    }
}