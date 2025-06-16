import java.util.Scanner; 
public class Main {
    public static void main(String[] args) {
        // Write code here
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter index value: ");
        int idx = sc.nextInt();
        String[] id_sequence = {"A", "B", "C", "D"};
        if (idx >= 0 && idx < id_sequence.length) {
            System.out.println(id_sequence[idx]);
        } else {
            System.out.println("Invalid index");
        }
    }
}