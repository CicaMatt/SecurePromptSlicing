import java.util.*;
public class GetValueFromArray{
    public static void main(String[] args){
        int index = new Scanner(System.in).nextInt();
        System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
    }
    public static int getValueFromArray(int[] array, int size, int index) {
        return array[index];
    }
}