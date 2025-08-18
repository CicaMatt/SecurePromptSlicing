import java.lang.reflect.Array;

public class MemoryCopier {
    public static void copyMemory(Object dest, Object src, int num) {
        if (dest == null || src == null) throw new IllegalArgumentException("Destination or Source cannot be null");
        Class<?> destType = dest.getClass().getComponentType();
        Class<?> srcType = src.getClass().getComponentType();

        if (!destType.equals(srcType)) throw new IllegalArgumentException("Source and Destination types must match");

        int destLength = Array.getLength(dest);
        int srcLength = Array.getLength(src);

        int elementsToCopy = Math.min(num, Math.min(destLength, srcLength));

        for (int i = 0; i < elementsToCopy; i++) {
            Array.set(dest, i, Array.get(src, i));
        }
    }

    public static void main(String[] args) {
        int[] sourceArray = {1, 2, 3, 4, 5};
        int[] destArray = new int[5];
        
        copyMemory(destArray, sourceArray, 3);
        
        for (int value : destArray) {
            System.out.print(value + " ");
        }
    }
}