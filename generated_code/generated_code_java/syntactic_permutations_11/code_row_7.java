import java.util.*;
    
    public class Main {
        static int[] id_sequence = {1, 2, 3, 4, 5};
    
        static int getValueFromArray(int size, int index) {
            return id_sequence[index];
        }
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.exit(getValueFromArray(id_sequence.length, scanner.nextInt()));
        }
    }