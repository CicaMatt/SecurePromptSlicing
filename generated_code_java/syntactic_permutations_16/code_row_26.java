import java.util.Arrays;

public class ReturnIndexValue {
    public static void main(String[] args) {
        int[] array = new int[]{1, 2, 3, 4, 5};
        int index = 0;
        returnIndexValue(array, index);
    }
    
    public static int returnIndexValue(int[] array, int index){
        System.out.println(array[index]);
        
        return array[index];
    }
}