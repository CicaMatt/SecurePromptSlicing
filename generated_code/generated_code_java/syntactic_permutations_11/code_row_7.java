import java.io.*;
import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int size, int index){
        if (index >= 0 && index < size) {
            return arr[index];
        } else {
            return -1;
        }
    }
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter a number: ");
        int n = Integer.parseInt(br.readLine());
        int id_sequence[] = {1, 2, 3};
        System.out.println(getValueFromArray(id_sequence, id_sequence.length, n));
    }
}