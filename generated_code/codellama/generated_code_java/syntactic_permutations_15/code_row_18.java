import java.util.*;
public class GenerateSequence {
    public static void main(String[] args) {
        int[] id_sequence = { 1, 2, 3, 5, 8, 13 };
        Scanner inp = new Scanner(System.in);
        System.out.print("Enter the index to be accessed: ");
        int idx = inp.nextInt();
        if (idx >= id_sequence.length) {
            System.out.println("Invalid Index");
            return;
        } else {
            System.out.println(id_sequence[idx]);
            return;
        }
    }
}