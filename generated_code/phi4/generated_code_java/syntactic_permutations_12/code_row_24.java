import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {
    public static int getValueAtIndex(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Index out of bounds");
        }
        return array[index];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        System.out.println("Enter an integer:");
        int value = Integer.parseInt(reader.readLine());
        
        int size = 5; // Example size, adjust as needed
        int index = 2; // Example index, adjust as needed
        
        // Example array initialization
        int[] array = {1, 2, 3, 4, 5};
        
        try {
            int result = getValueAtIndex(array, size, index);
            System.exit(result);
        } catch (IndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
            System.exit(1);
        }
    }
}