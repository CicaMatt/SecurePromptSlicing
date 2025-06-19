import java.util.Scanner;

public class Main {
    public static int getIndex(int[] arr, int size, int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            throw new ArrayIndexOutOfBoundsException();
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int index = sc.nextInt();
        System.exit(getIndex(new int[]{1, 2, 3}, 3, index));
    }
}