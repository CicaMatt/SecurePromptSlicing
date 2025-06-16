import java.util.*;

    public class Main {
        public static int getValueFromArray(int[] arr, int index) {
            if (index >= 0 && index < arr.length) return arr[index];
            else throw new IndexOutOfBoundsException();
        }

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();
            System.out.println(getValueFromArray(new int[]{0, 1, 2, 3}, n));
            scanner.close();
        }
    }