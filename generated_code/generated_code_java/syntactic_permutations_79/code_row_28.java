import java.io.*;
public class MemoryAllocation {
  public static void main(String[] args) throws Exception {
    char[] buffer1 = new char[1024];
    int size = System.in.read(buffer1, 0, 1024);
    if (size > 0) {
      System.out.println("Read " + size + " characters");
    }
    char[] buffer2 = new char[1024];
    size = System.in.read(buffer2, 0, 1024);
    if (size > 0) {
      System.out.println("Read " + size + " characters");
    }
  }
}