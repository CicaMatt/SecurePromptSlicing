import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println(fetchValueByIdx(id_sequence));
    }

    public static int fetchValueByIdx(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        int idx = scanner.nextInt();
        return id_sequence[idx];
    }
}