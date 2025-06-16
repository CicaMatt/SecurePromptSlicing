import java.util.*;
    
    public class Main {
        static int[] id_sequence = new int[]{2, 3, 5, 8, 11};
        static int getValueFromArray(int[] array, int size, int index) {
            if (index < 0 || index >= size) {
                return -1;
            }
            return array[index];
        }
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            int n = sc.nextInt();
            System.out.println("Exit code is: " + getValueFromArray(id_sequence, id_sequence.length, n));
        }
    }