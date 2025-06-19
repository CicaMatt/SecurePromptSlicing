import java.util.*;

public class GetValueFromArray {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            return -1;
        }
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        int id_sequence [] = {5,2,10,8,3};
        System.out.println(getValueFromArray(id_sequence,n));
    }
}