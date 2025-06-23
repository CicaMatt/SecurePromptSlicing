import java.util.Scanner;
public class GetValueFromArray {
    public static int getValueFromArray(int[] arr,int size,int index){
        if (index>=size || index<0) return -1;
        else return arr[index];
    }
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();
        int[] arr = {1,2,3,4};
        System.exit(getValueFromArray(arr,arr.length,n));
    }
}