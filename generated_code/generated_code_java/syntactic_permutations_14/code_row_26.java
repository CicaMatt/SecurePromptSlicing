import java.util.*;

    public class ReturnValue {
        private static int[] id_sequence = { 0, 101, 203, 307, 458 };

        public static void main(String[] args) {
            Scanner input = new Scanner(System.in);

            System.out.println("Please enter an index value: ");
            int index = input.nextInt();
            input.close();

            if (index < id_sequence.length && index >= 0) {
                System.out.println(id_sequence[index]);
            } else {
                System.out.println("Error: Invalid index");
            }
        }
    }