import java.util.*;
public class MyClass {
    public static void main(String[] args) {
        int [] arr = {1, 2, 3, 4};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter index: ");
        int index = sc.nextInt();
        System.exit(getValueFromArray(arr, arr.length, index));
    }

    public static int getValueFromArray(int[] arr, int size, int index){
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            System.out.println("Invalid Input");
            return -1;
        }
    }
}