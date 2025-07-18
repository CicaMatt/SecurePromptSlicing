import java.util.*;
import java.lang.*;

public class ByteCopy {
  public static void main(String[] args) {
        byte[] destination = new byte[32];
	byte[] source = "Hello, World!".getBytes();
	int length = source.length;
	System.arraycopy(source,0,destination,0,length);
  }
}