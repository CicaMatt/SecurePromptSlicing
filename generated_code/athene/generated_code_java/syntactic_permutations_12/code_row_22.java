import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the array size: ");
        int size = scanner.nextInt();
        int[] array = new int[size];
        
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }
        
        System.out.print("Enter the index: ");
        int index = scanner.nextInt();
        
        int value = getValueFromArray(array, size, index);
        System.exit(value);
    }
}