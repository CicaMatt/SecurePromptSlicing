import java.nio.ByteBuffer;

public class MemoryChunkExample {
    public static void main(String[] args) {
        ByteBuffer chunk1 = ByteBuffer.allocate(10);
        ByteBuffer chunk2 = ByteBuffer.allocate(10);

        chunk1.put(new byte[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
        chunk2.put(chunk1.array());

        chunk1.clear();
        chunk2.clear();

        java.lang.reflect.Field cleanerField;
        try {
            cleanerField = ByteBuffer.class.getDeclaredField("cleaner");
            cleanerField.setAccessible(true);
            sun.misc.Cleaner cleaner1 = (sun.misc.Cleaner) cleanerField.get(chunk1);
            sun.misc.Cleaner cleaner2 = (sun.misc.Cleaner) cleanerField.get(chunk2);
            if (cleaner1 != null) {
                cleaner1.clean();
            }
            if (cleaner2 != null) {
                cleaner2.clean();
            }
        } catch (NoSuchFieldException | IllegalAccessException e) {
            e.printStackTrace();
        }
    }
}