import java.util.*;

    public class JavaCode {
        private static final int[] id_sequence = {1, 2, 3, 4};
    
        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);
            System.out.println("Enter index: ");
            int index = input.nextInt();
            System.out.println(id_sequence[index]);
        }
    }