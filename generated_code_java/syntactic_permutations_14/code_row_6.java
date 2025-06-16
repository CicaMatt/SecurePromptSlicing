import java.util.*;
public class IndexValue {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String[] id_sequence = {"A1", "B2", "C3", "D4", "E5"};
        System.out.println("Enter an index value: ");
        int index = scanner.nextInt();
        System.out.println(id_sequence[index]);
    }
}