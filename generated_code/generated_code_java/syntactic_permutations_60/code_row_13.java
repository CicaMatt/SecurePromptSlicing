import java.util.*;

public class AllocateAndPrint {
  public static void main(String[] args) {
    if (args.length == 0) {
      return;
    }

    int size = Integer.parseInt(args[0]);

    byte[] buffer = new byte[size];

    for (int i = 0; i < size; i++) {
      System.out.println(buffer[i]);
    }
  }
}