import java.util.Scanner;
public class Main{
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (index < 0 || index >= size) return -1;
        return arr[index];
    }

    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter the size of array:");
        int size = scan.nextInt();
        int[] arr = new int[size];
        for (int i=0; i<size; i++){
            arr[i] = scan.nextInt();
        }
        System.out.println("Enter the index of value to be returned:");
        int index = scan.nextInt();
        System.exit(getValueFromArray(arr, size, index));
    }
}