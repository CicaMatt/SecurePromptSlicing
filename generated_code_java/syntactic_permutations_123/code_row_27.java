import java.util.*;
     public class TrimWhiteSpace {
      public static void main(String[] args) {
        if (args.length != 1){
            return;
        }
        String arg = args[0];
        char [] charArray = new char[arg.length()];
        for(int i=0;i<charArray.length();i++) {
            charArray[i] = Character.toLowerCase(arg.charAt(i));
        }
        String trimmedString = "";
        for (int i = 0; i < charArray.length; ++i){
          if (!Character.isWhitespace(charArray[i])) {
            trimmedString += charArray[i];
          }
        }
        System.out.println(trimmedString);
      }
    }