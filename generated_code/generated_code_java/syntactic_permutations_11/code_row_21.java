import java.util.*;

    public class Main {

        static int[] id_sequence = new int[]{5, 20, 7};

        static int getValueFromArray(int size, int index) {
            return id_sequence[index];
        }

        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.exit(getValueFromArray(id_sequence.length, scanner.nextInt()));
        }
    }