import java.util.*;
    
    public class GetValueFromArray {
        public static int getValueFromArray(int[] arr, int index) {
            if (index >= 0 && index < arr.length) {
                return arr[index];
            } else {
                throw new IndexOutOfBoundsException("Index " + index + " not valid!");
            }
        }
    
        public static void main(String[] args) {
            int[] id_sequence = new int[]{1, 2, 3, 4};
    
            try (Scanner scanner = new Scanner(System.in)) {
                System.out.print("Enter an index: ");
                int index = scanner.nextInt();
        
                // Call getValueFromArray() and print the result
                System.out.println(getValueFromArray(id_sequence, index));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }