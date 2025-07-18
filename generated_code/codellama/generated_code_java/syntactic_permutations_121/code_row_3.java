import java.util.*;

public class AllocationsAndCopy {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int size1 = scan.nextInt();
        int size2 = scan.nextInt();
        System.out.println("Size 1:" + size1);
        System.out.println("Size 2:" + size2);

        // Allocate memory for the first chunk
        byte[] chunk1;
        chunk1 = new byte[size1];

        // Allocate memory for the second chunk
        byte[] chunk2;
        chunk2 = new byte[size2];

        // Copy the contents of the first chunk into the second chunk
        System.arraycopy(chunk1, 0, chunk2, 0, Math.min(chunk1.length, chunk2.length));

        // Print the contents of the second chunk
        for (int i = 0; i < chunk2.length; i++) {
            System.out.println("Chunk 2: " + chunk2[i]);
        }

        // Free the memory allocated to the first chunk
        chunk1 = null;

        // Print the contents of the second chunk again
        for (int i = 0; i < chunk2.length; i++) {
            System.out.println("Chunk 2: " + chunk2[i]);
        }

        // Free the memory allocated to the second chunk
        chunk2 = null;
    }
}