public class Copier {

    public static void main(String[] args) {
        byte[] dest = new byte[10];
        String source = "Hello";
        byte[] src = source.getBytes();
        copy(dest, src, 5);
        System.out.println(new String(dest));
    }

    public static void copy(byte[] dest, byte[] src, int n) {
        for (int i = 0; i < n; i++) {
            dest[i] = src[i];
        }
    }
}