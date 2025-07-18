import java.nio.*;

class CopyMemory {
  public static void main(String args[]) {
    char[] src = {'H', 'e', 'l', 'l', 'o'};
    ByteBuffer dst = ByteBuffer.allocate(5);

    copyMemory(src, 0, 5);
    
    System.out.println("Copied String: " + new String(dst.array()));
  }
  
  static void copyMemory(char[] src, int offset, int length) {
    ByteBuffer bb = ByteBuffer.allocate(length);
    bb.asCharBuffer().put(src);

    byte[] bytes = new byte[length];
    bb.get(bytes, 0, length);

    for (int i=offset; i < offset + length; i++) {
      dst.put(i, bytes[i-offset]);
    }
  }
}