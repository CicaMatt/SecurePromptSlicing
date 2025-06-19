import java.nio.ByteBuffer;

public class ChunkCopy {
  public static void main(String[] args) {
    byte[] bytes1 = new byte[20];
    for (int i = 0; i < bytes1.length; ++i) {
      bytes1[i] = (byte) i;
    }
    ByteBuffer buffer = ByteBuffer.allocate(bytes1.length);
    buffer.put(bytes1);
    byte[] bytes2 = new byte[buffer.capacity()];
    for (int i = 0; i < bytes2.length; ++i) {
      bytes2[i] = buffer.get();
    }
    System.out.println(new String(bytes2));
  }
}