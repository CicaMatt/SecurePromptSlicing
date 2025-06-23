import java.util.*;

public class Main {
    public static int getValueFromArray(int[] arr, int index){
        return arr[index];
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.exit(getValueFromArray(new int[]{10, 20, 30},sc.nextInt()));
    }
}