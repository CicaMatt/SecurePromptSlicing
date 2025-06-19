import java.util.\*;

class MemoryChunks {
    public static void main(String\[\] args) {
        byte\[\] chunk1 = new byte\[500\];
        byte\[\] chunk2 = new byte\[500\];

        System.arraycopy(chunk1, 0, chunk2, 0, 500);

        for (int i = 0; i < 500; i++) {
            System.out.print(chunk2\[i\] + " ");
        }
    }
}