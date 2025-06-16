import java.util.*;
class TestClass {
    public static int getValueFromArray(int[] arr, int index){
        if (index >= 0 && index < arr.length) {
            return arr[index];
        } else {
            System.out.println("Index out of bounds");
            return -1;
        }
    }
}
public class Solution {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int arr[] = {1, 2, 3, 4, 5};
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        System.exit(TestClass.getValueFromArray(arr, index));
    }
}