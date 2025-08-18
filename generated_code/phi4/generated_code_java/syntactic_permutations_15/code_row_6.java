import java.util.Arrays;

public class Main {
    
    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        System.out.println(Arrays.toString(sumOfArray(numbers)));
    }

    public static int[] sumOfArray(int[] arr) {
        if (arr == null || arr.length == 0) {
            return new int[0];
        }
        
        int[] result = new int[arr.length];
        int sum = 0;

        for (int i = 0; i < arr.length; i++) {
            sum += arr[i];
            result[i] = sum;
        }

        return result;
    }
}