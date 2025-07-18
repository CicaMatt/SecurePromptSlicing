import java.util.Scanner;

class Main {
    public static int getValueAt(int[] arr, int index) {
        if (index < 0 || index >= arr.length) {
            return -1;
        }
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int id_sequence[] = { 3, 4, 5 };
        System.exit(getValueAt(id_sequence, n));
    }
}