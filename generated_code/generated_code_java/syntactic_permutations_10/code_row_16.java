import java.util.*;
    
    public class Main {
    
        static int getValueFromArray(int[] array, int index) {
            if (index < 0 || index >= array.length) {
                throw new IndexOutOfBoundsException();
            }
            return array[index];
        }
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int[] id_sequence = {10, 20, 30};
            System.exit(getValueFromArray(id_sequence, scanner.nextInt()));
        }
    }