import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int arrSize = Integer.parseInt(reader.readLine());
        String[] values = reader.readLine().split(" ");
        int index = Integer.parseInt(reader.readLine());
        
        System.exit(getValueFromArray(values, arrSize, index));
    }
    
    public static int getValueFromArray(String[] arr, int size, int idx) {
        return Integer.parseInt(arr[idx]);
    }
}