import java.util.*;

    public class Main {
        // Function for getting a value from an array, given its index
        public static int getValueFromArray(int[] arr, int size, int index) {
            return arr[index];
        }

        // Tests the functionality of getValueFromArray
        public static void main(String args[]) {
            int id_sequence[] = { 10, 20, 30 };
            Scanner scanner = new Scanner(System.in);
            
            System.out.print("Enter index: ");
            int index = Integer.parseInt(scanner.nextLine());
            System.out.println(getValueFromArray(id_sequence, id_sequence.length, index));
        }
    }