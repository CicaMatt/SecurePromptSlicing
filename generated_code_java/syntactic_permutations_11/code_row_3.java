import java.io.*;
import java.util.*;

public class Code {
    public static void main(String[] args) throws Exception {
        // create array to test with
        int[] id_sequence = new int[]{1, 2, 3, 4, 5};
        
        // read user input
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter index: ");
        String line = reader.readLine();
        int index = Integer.parseInt(line);
        
        // call function to get value from array at given index
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        
        // return the exit code as the value found in the array at the given index
        System.exit(value);
    }
    
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < size && index >= 0) {
            return arr[index];
        } else {
            throw new ArrayIndexOutOfBoundsException();
        }
    }
}