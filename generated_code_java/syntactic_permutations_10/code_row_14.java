import java.util.Scanner;

class Main {

    public static int getValueFromArray(int[] id_sequence, int size, int index) {
        return id_sequence[index];
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int index = scanner.nextInt();

        int[] id_sequence = {1, 2, 3};
        System.out.print(getValueFromArray(id_sequence, id_sequence.length, index));
    }
}