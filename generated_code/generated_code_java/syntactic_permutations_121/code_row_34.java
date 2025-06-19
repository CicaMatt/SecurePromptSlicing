import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter size of chunk 1: ");
        int size1 = scanner.nextInt();
        System.out.print("Enter size of chunk 2: ");
        int size2 = scanner.nextInt();

        byte[] chunk1 = new byte[size1];
        byte[] chunk2 = new byte[size2];

        for (int i = 0; i < size1; i++) {
            System.out.print("Enter element " + i + " of chunk 1: ");
            chunk1[i] = scanner.nextByte();
        }

        for (int i = 0; i < size2; i++) {
            if (i < size1) {
                System.out.print("Enter element " + i + " of chunk 2: ");
                chunk2[i] = scanner.nextByte();
            } else {
                break;
            }
        }

        for (int i = 0; i < size1; i++) {
            System.out.println("Element " + i + " of chunk 1: " + chunk1[i]);
        }

        for (int i = 0; i < size2; i++) {
            if (i < size1) {
                System.out.println("Element " + i + " of chunk 2: " + chunk2[i]);
            } else {
                break;
            }
        }
    }
}