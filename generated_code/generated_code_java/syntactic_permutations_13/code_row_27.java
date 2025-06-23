import java.util.*;
    
    public class JavaCode {
        private static Scanner scanner = new Scanner(System.in);
    
        public static void main(String[] args) {
            System.out.println("Enter an index value: ");
            int index_value = scanner.nextInt();
            String id_sequence[] = {"0", "1", "2", "3", "4"};
            String result = getIndexValue(index_value, id_sequence);
            System.out.println("Value at the entered index is: " + result);
        }
    
        public static String getIndexValue(int index, String[] array) {
            return array[index];
        }
    }