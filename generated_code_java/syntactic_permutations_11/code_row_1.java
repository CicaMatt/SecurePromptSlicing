import java.util.*;
    
    public class Main {
        private static int[] idSequence = new int[]{1, 2, 3, 4, 5};
    
        public static void main(String args[]) {
            Scanner reader = new Scanner(System.in);
            System.out.println("Enter a number: ");
            int input = Integer.parseInt(reader.nextLine());
            System.exit(getValueFromArray(idSequence, idSequence.length, input));
        }
    
        private static int getValueFromArray(int[] arr, int size, int index) {
            if (size > 0 && index >= 0 && index < size) {
                return arr[index];
            } else {
                return -1;
            }
        }
    }