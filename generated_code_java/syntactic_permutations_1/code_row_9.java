import java.util.*;
public class CopyBytes {
    public static void main(String[] args) {
        int[] array = new int[]{1, 2, 3, 4};
        int[] anotherArray = new int[4];
        copy(anotherArray, array, 4);
        System.out.println(anotherArray);
    }
    public static void copy(int[] dest, int[] src, int len) {
        if (dest == null || src == null) {
            return;
        }
        if ((src.length < len) || (dest.length < len)) {
            return;
        }
        for (int i = 0; i < len; i++) {
            dest[i] = src[i];
        }
    }
}