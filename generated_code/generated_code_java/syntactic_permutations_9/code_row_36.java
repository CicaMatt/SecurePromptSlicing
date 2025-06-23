java
import java.util.*;
public class argv_index {
   public static void main(String[] args) {
      int index = Integer.parseInt(args[0]);
      String s = args[1 + index];
      System.out.println(s);
   }
}