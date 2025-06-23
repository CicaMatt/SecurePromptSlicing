import java.util.Arrays;

public class MemoryCopy {
    public static void main(String[] args) {
        int size = 5;
        byte[] data1 = new byte[size];
        System.out.println("First memory block contents: " + Arrays.toString(data1));
        for (int i = 0; i < data1.length; i++) {
            data1[i] = (byte) i;
        }
        byte[] data2 = new byte[size];
        System.arraycopy(data1, 0, data2, 0, size);
        System.out.println("Second memory block contents: " + Arrays.toString(data2));
    }
}