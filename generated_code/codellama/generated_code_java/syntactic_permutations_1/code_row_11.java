import java.nio.charset.*;
public class CopyBytes {
  public static byte[] copy(byte[] dest, byte[] src) {
      System.arraycopy(src, 0, dest, 0, Math.min(dest.length, src.length));
    return dest;
  }
}