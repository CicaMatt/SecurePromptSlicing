public class CopyBytes {
    public static void main(String[] args) {
        byte[] dest = new byte[args.length];
        byte[] src = new byte[args.length];
        for (int i = 0; i < args.length; i++) {
            src[i] = Byte.parseByte(args[i]);
            dest[i] = src[i];
        }
    }
}