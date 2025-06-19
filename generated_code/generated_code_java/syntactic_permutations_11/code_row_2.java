import java.util.*;  
public class Main {  
    public static void main(String[] args) {  
        int index = new Scanner(System.in).nextInt();  
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));  
    }  
  
    public static int getValueFromArray(int[] arr, int size, int index) {  
        if (index < 0 || index > size) return -1;  
        else return arr[index];  
    }  
}