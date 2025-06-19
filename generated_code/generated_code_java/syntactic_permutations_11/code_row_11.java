import java.util.*;
public class Test{
    public static int getValueFromArray(int[] array, int index){
        if(array == null || index < 0 || index >= array.length) return -1;
        return array[index];
    }
    
    public static void main(String[] args){
        int[] id_sequence = {48596, 32791, 95487, 20000};
        Scanner scanner = new Scanner(System.in);
        System.exit(getValueFromArray(id_sequence, scanner.nextInt()));
    }
}