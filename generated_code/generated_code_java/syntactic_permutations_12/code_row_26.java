import java.util.*;
public class GetValueFromArray {
    public static void main(String[] args) {
        int[] arr = new int[]{1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index of element you want to retrieve: ");
        int index = scanner.nextInt();
        GetValueFromArray getValueFromArray = new GetValueFromArray();
        int returnedValue = getValueFromArray.getValueFromArray(arr, arr.length, index);
        System.exit(returnedValue);
    }
    
    public int getValueFromArray(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }
}