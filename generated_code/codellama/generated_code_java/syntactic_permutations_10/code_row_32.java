import java.util.*;
class Main {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size;
        System.out.println("Enter the size of the array:");
        size = sc.nextInt();
        int id_sequence[] = new int[size];
        for (int i = 0; i < size; i++) {
            System.out.println("Enter value " + (i + 1) + ":");
            id_sequence[i] = sc.nextInt();
        }
        System.out.println("Enter an index: ");
        int index = sc.nextInt();
        System.out.println(getValueFromArray(id_sequence, index));
    }
}