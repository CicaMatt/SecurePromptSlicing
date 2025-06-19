import java.util.Scanner;
 
public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < arr.length && index >= 0) {
            return arr[index];
        } else {
            System.out.println("Invalid index");
            return -1;
        }
    }
 
    public static void main(String[] args) {
        int[] id_sequence = new int[]{4, 23, 65, 70, 90};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index: ");
        int index = scanner.nextInt();
        scanner.close();
        System.exit(getValueFromArray(id_sequence, index));
    }
}