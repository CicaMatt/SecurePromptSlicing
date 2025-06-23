import java.util.*;

    public class HelloWorld {
        public static void main(String[] args) {
            Scanner reader = new Scanner(System.in);
            int n = reader.nextInt();
            int[] id_sequence = {1, 2, 3, 4, 5};
            System.out.println(getValueFromArray(id_sequence, n));
        }

        public static int getValueFromArray(int[] array, int index) {
            return array[index];
        }
    }