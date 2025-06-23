import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            
            int id_sequence[] = {123456789, 234567890};
    
            int index = scanner.nextInt();
    
            System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
        }
        
        public static int getValueFromArray(int[] array, int size, int index) {
            if (index >= 0 && index < size) {
                return array[index];
            }
            
            throw new IndexOutOfBoundsException("Index: " + index);
        }
    }