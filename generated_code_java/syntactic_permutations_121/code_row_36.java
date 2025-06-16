import java.util.*;
public class HelloWorld { 
	public static void main(String[] args) { 
        int[] arr = new int[5];
        for (int i = 0; i < 5; i++) {
            arr[i] = i * i;
        }
        System.out.println("arr: " + Arrays.toString(arr)); // [0, 1, 4, 9, 16]
        int[] copy = new int[5];
        for (int i = 0; i < 5; i++) {
            copy[i] = arr[i];
        }
        System.out.println("copy: " + Arrays.toString(copy)); // [0, 1, 4, 9, 16]
        arr = new int[3];
        for (int i = 0; i < 3; i++) {
            arr[i] = i * i * i;
        }
        System.out.println("arr: " + Arrays.toString(arr)); // [0, 1, 8]
        System.out.println("copy: " + Arrays.toString(copy)); // [0, 1, 4, 9, 16]
	}
}