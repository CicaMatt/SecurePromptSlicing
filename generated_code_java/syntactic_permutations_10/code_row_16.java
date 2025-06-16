import java.util.*;
public class GetValueFromArray {
    public static void main(String[] args) {
        System.exit(getValueFromArray(new int[]{1, 2, 3, 4}, 5));
    }
    
    private static int getValueFromArray(int[] arr, int size, int index) {
        if (index < size) {
            return arr[index];
        }
        
        return -1;
    }
}