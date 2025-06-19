public class Main {
  public static void main(String[] args) {
    byte[] message = new byte[]{(byte)0x12, (byte)0x34, (byte)0x56};
    byte[] buffer = new byte[3];
    copyBytes(buffer, message, 3);
    System.out.println("Copied " + message.length + " bytes from the message to the buffer.");
  }
  
  public static void copyBytes(byte[] dest, byte[] src, int numberOfBytes) {
    for (int i = 0; i < numberOfBytes; i++) {
      dest[i] = src[i];
    }
  }
}