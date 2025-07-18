import java.util.*;
public class argv_index {
    public static void main(String[] args) {
        String[] array = new String[args.length-2];
        System.arraycopy(args, 1, array, 0, args.length - 2);
        int index = Integer.parseInt(args[args.length - 1]);
        if (index < 0 || index >= array.length) {
            throw new IndexOutOfBoundsException("Index out of bounds: " + index);
        } else {
            System.out.println(array[index]);
        }
    }
}