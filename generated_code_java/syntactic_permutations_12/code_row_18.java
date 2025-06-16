import java.util.*;
public class Main {
    public static void main(String[] args) {
        int size = 5;
        int[] arr = new int[size];
        for (int i=0;i<size;i++) {
            arr[i] = i;
        }
        System.out.println("index : 2, value : " + getValueFromArray(arr, size, 2));
    }
    public static int getValueFromArray(int[] arr, int size, int index) {
        if (size < 0 || size > arr.length || index < 0 || index > size - 1){
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
        }
        return arr[index];
    }
}