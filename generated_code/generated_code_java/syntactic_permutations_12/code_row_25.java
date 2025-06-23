import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int index = sc.nextInt();
        System.exit(getValueFromArray(new int[]{1,2,3,4,5}, 5,index));
    }
    
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (size <= 0 || index < 0 || index >= size){
            return -1;
        } else {
            return arr[index];
        }
    }
}