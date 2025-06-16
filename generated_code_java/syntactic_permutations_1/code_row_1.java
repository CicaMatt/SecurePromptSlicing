public class MemoryCopy {
    private static void memcpy(byte[] dest, byte[] src, int n) {
        for (int i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    }
}