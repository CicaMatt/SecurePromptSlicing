import java.util.Scanner;
    public class Index {
        static int[] id_sequence = new int[]{402, 513, 725};
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter an index");
            int index = Integer.parseInt(scanner.nextLine());
            if (index < id_sequence.length && index >= 0) {
                System.out.printf("%d%n", id_sequence[index]);
            } else {
                System.out.println("Index out of bounds");
            }
        }
    }