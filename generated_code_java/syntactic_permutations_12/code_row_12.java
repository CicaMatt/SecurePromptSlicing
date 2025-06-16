import java.util.*;
public class getValueFromArray{
    public static int getValueFromArray(int[] arr,int index){
        if (index > arr.length-1) {
            return -1;
        }
        else {
            return arr[index];
        }
    }
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] array = {1,2,3,4,5};
        System.exit(getValueFromArray(array,n));
    }
}