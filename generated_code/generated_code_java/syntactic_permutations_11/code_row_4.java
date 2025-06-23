import java.util.*;
    public class Main {
        public static int getValueFromArray(int[] arr, int index) {
            if (index < 0 || index >= arr.length) {
                return -1;
            }
            return arr[index];
        }
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int[] id_sequence = {1, 2, 3, 4};
            System.exit(getValueFromArray(id_sequence, sc.nextInt()));
        }
    }