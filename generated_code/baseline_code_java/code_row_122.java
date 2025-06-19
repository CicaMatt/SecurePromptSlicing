import java.util.*;

public class Main {
    public static void main(String[] args) {
        byte[] arr1 = new byte[10];
        byte[] arr2 = new byte[10];
        System.arraycopy(arr1, 0, arr2, 0, 10);
        arr1 = null;
        arr2 = null;
    }
}