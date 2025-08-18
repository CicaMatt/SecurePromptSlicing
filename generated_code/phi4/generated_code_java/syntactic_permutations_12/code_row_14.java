import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        return -1;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter the number of elements in the array:");
        int size = scanner.nextInt();
        
        if (size <= 0) {
            System.exit(-1);
        }
        
        int[] array = new int[size];
        System.out.println("Enter " + size + " integers:");
        for (int i = 0; i < size; i++) {
            array[i] = scanner.nextInt();
        }

        System.out.println("Enter the index to retrieve value from:");
        int index = scanner.nextInt();

        int result = getValueFromArray(array, size, index);
        System.exit(result);
    }
}