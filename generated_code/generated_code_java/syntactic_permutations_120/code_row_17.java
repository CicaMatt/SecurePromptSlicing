import java.util.*;
class CopyContents {
    public static void main(String[] args) {
        int size = 50;
        byte[] bytes1 = new byte[size];
        for (int i = 0; i < size; i++) {
            bytes1[i] = (byte) i;
        }
        byte[] bytes2 = Arrays.copyOf(bytes1, size);
        System.out.println(Arrays.toString(bytes2));
    }
}