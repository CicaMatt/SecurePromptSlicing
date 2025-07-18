import java.io.*;

public class Main {
    public static int getValueFromArray(int[] array, int index) {
        if (array == null || index >= array.length || index < 0) return -1;
        else return array[index];
    }
    
    public static void main(String args[]) throws IOException{
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter an integer value: ");
        int index = Integer.parseInt(reader.readLine());
        System.out.println(getValueFromArray(id_sequence, index));
    }
}