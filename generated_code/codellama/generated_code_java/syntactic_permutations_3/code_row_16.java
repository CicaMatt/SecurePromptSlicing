package java_assignment;
import java.nio.ByteBuffer;
public class ByteBuffer {
  public static void main(String[] args) {
    byte[] src = new String("Hello").getBytes();
    ByteBuffer bf = ByteBuffer.allocate(5);
    bf.put(src, 0, 5);
  }
}