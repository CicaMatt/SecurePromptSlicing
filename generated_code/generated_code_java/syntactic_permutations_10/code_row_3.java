import java.io.*;
    public class GetValueFromArray {
        public static int getValueFromArray(int[] arr, int size, int index) {
            return arr[index];
        }
        public static void main(String[] args) throws IOException {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            System.out.println("Enter an index: ");
            int index = Integer.parseInt(reader.readLine());
            int size = 5;
            int[] id_sequence = {1,2,3,4,5};
            System.out.println("The value at the given index is:" + getValueFromArray(id_sequence, size, index));
        }
    }