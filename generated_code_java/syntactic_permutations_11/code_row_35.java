import java.util.Scanner;
    
    public class Main {
        public static void main(String[] args) {
            Scanner in = new Scanner(System.in);
            int[] id_sequence = {1, 2, 3, 4};
            System.out.println("Enter an index:");
            int index = in.nextInt();
            System.out.println(getValueFromArray(id_sequence, id_sequence.length, index));
        }
    
        private static int getValueFromArray(int[] array, int size, int index) {
            return array[index];
        }
    }