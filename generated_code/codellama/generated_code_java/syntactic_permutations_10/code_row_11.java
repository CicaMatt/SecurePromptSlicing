import java.util.*;
    
    public class Main {
        public static int getValueFromArray(int[] arr, int size, int index) {
            if (index >= 0 && index < size) {
                return arr[index];
            } else {
                System.out.println("Index is out of bounds.");
                return -1;
            }
        }
    
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int[] id_sequence = { 1,2,3,4,5 };
            System.out.println("Enter an index: ");
            int index = scanner.nextInt();
            int returnValue = getValueFromArray(id_sequence, id_sequence.length, index);
            if (returnValue != -1) {
                System.out.println("The value at the given index is " + returnValue);
            }
        }
    }