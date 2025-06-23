import java.util.*;
class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index < 0 || index > arr.length - 1) {
            throw new ArrayIndexOutOfBoundsException();
        }
        return arr[index];
    }

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an integer: ");
        int value = scanner.nextInt();
        System.exit(getValueFromArray(new int[]{1, 2, 3}, value));
    }
}