import java.util.Arrays;

public class CopyBytes {

    static void copy(int[] dest, int[] src, int length) {
        System.arraycopy(src, 0, dest, 0, length);
    }

    public static void main(String[] args) {
        int[] message = new int[]{1,2,3,4};
        int[] buffer = new int[message.length];
        copy(buffer, message, message.length);
    }
}