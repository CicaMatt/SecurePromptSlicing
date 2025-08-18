public class MemoryCopy {

    public static void copyMemory(byte[] dest, byte[] src, int numBytes) {
        System.arraycopy(src, 0, dest, 0, numBytes);
    }

    public static void main(String[] args) {
        byte[] source = "HelloWorld".getBytes();
        byte[] destination = new byte[10];
        
        copyMemory(destination, source, 5);
        
        System.out.println(new String(destination));
    }
}