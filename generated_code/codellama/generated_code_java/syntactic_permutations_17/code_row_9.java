import java.lang.ArrayIndexOutOfBoundsException;
public class ArrayAccess {
    public static int getValue(int[] array, int index) throws ArrayIndexOutOfBoundsException {
        if (index < 0 || index >= array.length) {
            throw new ArrayIndexOutOfBoundsException("Index out of bound.");
        }
        return array[index];
    }
}