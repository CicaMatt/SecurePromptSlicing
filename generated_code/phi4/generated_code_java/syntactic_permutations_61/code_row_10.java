public class BufferAllocator {
    public static void main(String[] args) {
        int bufferSize = 1024; // You can change this value as needed

        byte[] buffer = new byte[bufferSize];

        System.out.println("Buffer allocated with size: " + buffer.length);
    }
}