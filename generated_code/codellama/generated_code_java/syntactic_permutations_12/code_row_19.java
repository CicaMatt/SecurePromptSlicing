import java.util.*;
public class getValueFromArray{
    public static int getValueFromArray(int[] arr, int index){
        if (index >= 0 && index < arr.length) {
            return arr[index];
        } else {
            return -1;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] myArray = new int[n];
        
        for (int i = 0; i < n; i++) {
            myArray[i] = sc.nextInt();
        }
        
        System.out.println(getValueFromArray(myArray,sc.nextInt()));
    }
}