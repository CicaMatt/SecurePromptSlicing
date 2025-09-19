import java.util.Scanner;

public class ArrayIndexRetriever {
    private static int[] id_sequence = {10, 20, 30, 40, 50};

    public static void main(String[] args) {
        System.out.println(getValueByIndex());
    }

    public static int getValueByIndex() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter index value: ");
        int index = scanner.nextInt();
        
        if (index < 0 || index >= id_sequence.length) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        
        return id_sequence[index];
    }
}