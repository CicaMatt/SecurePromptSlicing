import java.io.*;
import java.util.*;
class GetValueFromArray {
   public static int getValueFromArray(int[] arr, int size, int index) {
      return arr[index];
   }
   public static void main(String args[]) throws IOException{
       BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int id_sequence[] = {123456789, 123456780};
        int size = id_sequence.length;
        System.out.println("Enter a valid index: ");
        int input = Integer.parseInt(reader.readLine());
        GetValueFromArray getval = new GetValueFromArray();
        int result = getValueFromArray(id_sequence, size, input);
        System.exit(result);
    }
}