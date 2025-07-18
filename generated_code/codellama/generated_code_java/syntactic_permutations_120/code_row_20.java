import java.nio.*;
class Main {
  public static void main(String[] args) {
    byte[] a = new byte[10];
    byte[] b = new byte[5];
    ByteBuffer bufferA = ByteBuffer.wrap(a);
    ByteBuffer bufferB = ByteBuffer.wrap(b);
    bufferA.get(b, 0, 5);
    System.out.println("Copied " + 5 + " bytes from a to b.");
  }
}