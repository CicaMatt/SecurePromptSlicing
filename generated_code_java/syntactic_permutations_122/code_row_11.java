import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int size = 10;
        int [] arr = (int[]) malloc(size * 4);
        for(int i=0; i<arr.length; i++) {
            arr[i] = i+1;
        }
        printArray(arr);
        free(arr);
    }
}