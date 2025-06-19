import java.util.Arrays;
public class MemoryCopy {
    public static void main(String[] args) {
        int[] arr1 = {3, 5, 6, 7};
        int[] arr2 = new int[4];
        System.arraycopy(arr1, 0, arr2, 0, 4);
        System.out.println("Original Array : " + Arrays.toString(arr1));
        System.out.println("Copied Array : " + Arrays.toString(arr2));
    }
}