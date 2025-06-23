import java.util.Scanner;
public class ArrayIndex {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index;
        System.out.print("Enter an index value: ");
        index = sc.nextInt();
        int id_sequence [] = {3, 8, 6, 2, 9};
        for (int i = 0; i < id_sequence.length; i++) {
            if (i == index) {
                System.out.println(id_sequence[index]);
            }
        }
    }
}