import java.util.*;
    
    public class getValueFromArray {
        static int getValue(int[] arr, int index){
            if(arr.length - 1 >= index && index >= 0) {
                return arr[index];
            } else {
                System.out.println("Invalid Index");
                return -1;
            }
        }
    
    public static void main(String[] args){
        int[] id_sequence = new int[]{1, 2, 3};
        Scanner scanner = new Scanner(System.in);
        System.exit(getValue(id_sequence, scanner.nextInt()));
    }
}