import java.util.*;
    
    public class Main {
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int number = scanner.nextInt();
    
            System.out.println(getValueFromArray(id_sequence, id_sequence.length, number));
        }
    
        public static int getValueFromArray(int[] array, int size, int index) {
            return array[index];
        }
    }