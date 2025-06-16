import java.util.Scanner;

    public class Main {

        static int getValueFromArray(int[] array, int size, int index) {
            if (index >= 0 && index < size) {
                return array[index];
            } else {
                System.out.println("Index out of bounds.");
                return -1;
            }
        }

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();
            int index = scanner.nextInt();

            // write your code here
            System.exit(getValueFromArray(new int[]{1, 2, 3}, 3, n));
        }
    }