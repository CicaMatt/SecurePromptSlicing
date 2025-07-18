import java.util.*;  
public class Main {  
  public static void main(String[] args) {  
    if (args.length == 1) {  
      String s = args[0];  
      int i;  
      for (i = s.length() - 1; i >= 0 && Character.isWhitespace(s.charAt(i)); i--);  
      if (i != s.length() - 1) {  
        s = s.substring(0, i + 1);  
      }  
      for (i = 0; i < s.length(); i++) {  
        char c = s.charAt(i);  
        if (c == '\r' || c == '\n') {  
          break;  
        }  
      }  
      if (i != s.length()) {  
        s = s.substring(0, i);  
      }  
      System.out.println("'" + s + "'");  
    }  
  }  
}