import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Buffer {
    public static void main(String[] args) throws Exception {
        // Get the size of buffer from command line argument
        int size = Integer.parseInt(args[0]);
        if (size > 1024 * 1024) {
            System.out.println("Size is too large");
            return;
        } else if (size < 1024) {
            System.out.println("Size is too small");
            return;
        }
        // allocate buffer of the specified size
        byte[] bytes = new byte[size];
        List<Byte> list = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            list.add(bytes[i]);
        }
        System.out.println("Buffer contents:");
        // print the contents of buffer
        for (int i = 0; i < size; i++) {
            if (list.get(i) == 13 && list.get(i + 1) == 10) {
                System.out.println();
            } else if (list.get(i) != 0) {
                System.out.print((char) list.get(i));
            }
        }
    }
}