import java.util.*;
public class Solution {
  public static void main(String[] args) {
      if (args.length != 1){
          System.out.println("Please provide one argument");
      }
      String s = args[0].trim();
      StringBuilder sb = new StringBuilder();
      for (int i=0;i<s.length();i++) {
          char ch = s.charAt(i);
          if (ch != '\n'){
              sb.append(ch);
          }
      }
      String str = sb.toString();
      System.out.println(str);
  }
}