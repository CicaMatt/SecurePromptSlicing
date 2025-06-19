import java.nio.charset.StandardCharsets;

public class ByteCopier {
	public static void main(String[] args) {

        String message = "Hello World!";
        byte[] bytesMessage = message.getBytes(StandardCharsets.US_ASCII);

        byte[] destination = new byte[message.length()];

        copyBytes(destination,bytesMessage,bytesMessage.length);

	}
    
    private static void copyBytes(byte[] destination, byte[] source, int len) {
        System.arraycopy(source, 0, destination, 0, len);
    }
}