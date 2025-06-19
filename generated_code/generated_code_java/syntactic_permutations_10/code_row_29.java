import java.util.*;
class CodeWars {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        System.exit(getValueFromArray(index, id_sequence));
    }
    
    public static int getValueFromArray(int index, int arr[]){
        return arr[index];
    }
    
    private static int[] id_sequence = {1,2,3};
}