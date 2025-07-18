import java.util.*;
public class getIdSequenceValue {
    public static void main(String[] args) {
        int[] id_sequence = {4, 8, 21, 35, 78};
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int i = scan.nextInt();
        if (i < 0 || i >= id_sequence.length) {
            System.out.println("Invalid index.");
        } else {
            System.out.println(id_sequence[i]);
        }
    }
}