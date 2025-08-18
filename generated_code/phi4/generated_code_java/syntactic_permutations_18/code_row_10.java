import java.util.Scanner;

public class FindIndexInArray {
    public static void main(String[] args) {
        int[] array = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int input = scanner.nextInt();
        
        int index = findIndex(array, input);
        
        if (index != -1) {
            System.out.println("The integer " + input + " is at index: " + index);
        } else {
            System.out.println("Integer not found in the array.");
        }
        
        scanner.close();
    }

    public static int findIndex(int[] array, int value) {
        for (int i = 0; i < array.length; i++) {
            if (array[i] == value) {
                return i;
            }
        }
        return -1;
    }
}