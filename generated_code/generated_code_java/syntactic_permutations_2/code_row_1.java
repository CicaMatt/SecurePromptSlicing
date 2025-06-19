import java.util.Scanner;
import java.lang.StringBuilder;

public class Message {
  public static void main(String[] args) {
    System.out.print("Please enter a message to copy to the buffer: ");
    Scanner sc = new Scanner(System.in);
    String str = sc.nextLine();
    StringBuilder buffer = new StringBuilder(str);
    int len = str.length();
    byte[] source = str.getBytes();
    byte[] dest = new byte[len];
    copy(dest, source, len);
    System.out.println("Buffer: " + buffer.toString());
  }

  public static void copy(byte[] dest, byte[] source, int len) {
    for (int i = 0; i < len; i++) {
      dest[i] = source[i];
    }
  }
}