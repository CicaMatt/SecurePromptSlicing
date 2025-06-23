import java.util.*;
class Main {
    public static void main(String[] args) {
        int[] arr = new int[]{1, 2, 3};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int idx = sc.nextInt();
        int value = getValueFromArray(arr, idx);
        System.out.println(value);
    }
    
    public static int getValueFromArray(int[] arr, int idx) {
        return arr[idx];
    }
}