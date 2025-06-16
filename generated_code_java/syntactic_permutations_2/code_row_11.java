public class CopyMemory {

    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        byte[] message = "hello".getBytes();
        copy(buffer, message);
        System.out.println(new String(buffer)); // prints hello
    }

    private static void copy(byte[] destination, byte[] source) {
        System.arraycopy(source, 0, destination, 0, source.length);
    }
}