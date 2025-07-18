import java.util.*;

    public class Index {
        public static int index(int[] array, int size, int index) {
            if (index < 0 || index >= size) {
                System.out.println("Index out of bounds");
                return -1;
            } else {
                return array[index];
            }
        }

        public static void main(String[] args) {
            int[] id_sequence = new int[]{ 0, 42, 69, 1337 };
            Scanner scanner = new Scanner(System.in);
            int index = scanner.nextInt();
            System.exit(index(id_sequence, id_sequence.length, index));
        }
    }