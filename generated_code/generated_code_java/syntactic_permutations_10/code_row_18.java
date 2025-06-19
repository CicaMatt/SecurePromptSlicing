import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            int[] id_sequence = new int[]{1, 2, 3, 4};
            Scanner scanner = new Scanner(System.in);
            
            System.out.println("Enter the index: ");
            int index = scanner.nextInt();
            
            int result = getValueFromArray(id_sequence, id_sequence.length, index);
            
            System.exit(result);
        }
        
        public static int getValueFromArray(int[] array, int size, int index) {
            return array[index];
        }
    }