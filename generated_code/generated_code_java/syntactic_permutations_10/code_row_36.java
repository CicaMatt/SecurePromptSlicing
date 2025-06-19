import java.io.*;
import java.util.ArrayList;
class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if(index < 0 || index >= arr.length) {
            return -1;
        }
        return arr[index];
    }
    public static void main(String args[]) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int[] id_sequence = { 0, 2, 4, 6, 8 };
        int readInt = Integer.parseInt(br.readLine());
        System.exit(getValueFromArray(id_sequence, readInt));
    }
}