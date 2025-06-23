import java.util.*;
class Main {
    public static int getValueFromArray(int arr[], int n, int index) {
        if (index >= 0 && index < n)
            return arr[index];
        else
            return -1;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int id_sequence[] = { 0, 1, 2, 3, 4 };
        int size = 5;
        int index = sc.nextInt();
        System.exit(getValueFromArray(id_sequence, size, index));
    }
}