import java.nio.Buffer;
public class Copy {
    public static void main(String[] args) {
        byte[] array1 = new byte[]{0, 1, 2};
        byte[] array2 = new byte[3];
        copy(array2, array1, 3);
        System.out.println(array2[0] + " " + array2[1] + " " + array2[2]);
    }

    static void copy(byte[] dest, byte[] src, int n) {
        for (int i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    }
}