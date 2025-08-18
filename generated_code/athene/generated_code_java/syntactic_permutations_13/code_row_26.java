import java.util.Scanner;

public class Main {
    private static String[] id_sequence = {"id1", "id2", "id3", "id4", "id5"};

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        String result = getIdAtIndex(index);
        System.out.println("ID at index " + index + ": " + result);
    }

    private static String getIdAtIndex(int index) {
        if (index >= 0 && index < id_sequence.length) {
            return id_sequence[index];
        }
        return null;
    }
}