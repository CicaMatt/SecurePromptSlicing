import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter index value: ");
        int index = sc.nextInt();
        String[] id_sequence = {"01", "02", "03"};
        if (index < 0 || index >= id_sequence.length) {
            System.out.println("Invalid index");
            return;
        }
        System.out.println(id_sequence[index]);
    }
}