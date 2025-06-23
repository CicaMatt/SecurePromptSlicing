import java.util.*;
public class BufferAllocator {
  public static void main(String[] args) {
      int buffersize = Integer.parseInt(args[0]);
      byte[] buffer = new byte[buffersize];
      System.out.println("Contents of the buffer :");
      for (int i=0; i<buffer.length;i++){
          System.out.print((char)buffer[i]);
      }
  }
}