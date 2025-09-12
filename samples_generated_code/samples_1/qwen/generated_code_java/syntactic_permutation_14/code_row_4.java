import java.util.Scanner;

public class IndexValueRetriever {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        IndexValueRetriever retriever = new IndexValueRetriever();
        System.out.println(retriever.getValueAtIndex(id_sequence));
    }

    public int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        scanner.close();

        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            throw new IndexOutOfBoundsException("Index " + index + " is out of bounds for length " + array.length);
        }
    }
}