public class MemoryCopy {
    public static void main(String[] args) {
        byte[] chunk = new byte[10];
        System.arraycopy(chunk, 0, chunk, 10, 10);
        chunk = null;
    }
}