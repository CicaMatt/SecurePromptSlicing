import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }

    private static int getValueFromArray(int[] idSequence, int size, int index) {
        return idSequence[index];
    }
}