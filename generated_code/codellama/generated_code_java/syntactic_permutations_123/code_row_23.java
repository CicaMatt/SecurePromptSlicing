import java.util.*;

public class RemoveTrailingWhitespace {
   public static void main(String[] args) {
      if (args.length == 1 && !args[0].isEmpty()) {
         String s = args[0];
         int length = s.length();
         while (Character.isWhitespace(s.charAt(length - 1))) {
            length--;
         }
         s = s.substring(0, length);
      }
   }
}