import java.util.Scanner;

public class IndexSequence {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the index value");
        int i = sc.nextInt();
        id_sequence[i] = 1;
        for (int j = 0; j < id_sequence.length; j++) {
            if (j != i) {
                id_sequence[j] = 0;
            }
        }
    }

    public static int getValue(int index) {
        return id_sequence[index];
    }
}