import java.util.*;
public class Main {
    public static void main(String[] args) {
        int[] id_sequence = new int[]{1,2,3};
        Scanner sc = new Scanner(System.in);
        System.exit(getValueFromArray(id_sequence,sc.nextInt()));
    }
    
    public static int getValueFromArray(int[] array, int index){
        return array[index];
    }
}