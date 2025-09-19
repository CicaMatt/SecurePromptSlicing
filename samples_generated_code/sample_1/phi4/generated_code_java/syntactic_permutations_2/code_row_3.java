public class MemoryCopy {
    public static void main(String[] args) {
        byte[] source = "Hello, World!".getBytes();
        byte[] destination = new byte[source.length];
        
        // Number of bytes to copy
        int numberOfBytesToCopy = 5;

        // Copy bytes from source to destination
        System.arraycopy(source, 0, destination, 0, numberOfBytesToCopy);

        // Convert the copied bytes back to a string and print it
        String copiedMessage = new String(destination).trim();
        System.out.println("Copied message: " + copiedMessage);
    }
}