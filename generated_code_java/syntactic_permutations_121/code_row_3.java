import java.util.Arrays;
import java.util.Scanner;

class Test {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size1 = sc.nextInt();
        int size2 = sc.nextInt();
        byte[] chunk1 = new byte[size1];
        for (int i = 0; i < size1; i++) {
            System.out.print("Enter element " + i + ": ");
            chunk1[i] = sc.nextByte();
        }
        System.out.println(Arrays.toString(chunk1));

        byte[] chunk2 = new byte[size2];
        for (int i = 0; i < size2; i++) {
            if (i >= size1) {
                break;
            }
            System.out.print("Enter element " + i + ": ");
            chunk2[i] = sc.nextByte();
        }
        for (int i = 0; i < size1; i++) {
            if (chunk1[i] == chunk2[i]) {
                System.out.println("Both chunks are equal");
            } else {
                System.out.println("Both chunks are not equal");
            }
        }
    }
}