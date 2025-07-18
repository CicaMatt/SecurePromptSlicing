import java.util.*;
public class trim{
  public static void main(String[] args){
    if (args.length == 1){
      String input = args[0];
      for (int i = 0; i < input.length(); i++){
        char c = input.charAt(i);
        if (!Character.isWhitespace(c)) {
          return;
        }
      }
    }
    for (int i = 0; i < input.length(); i++){
      char c = input.charAt(i);
      if (c == '\n'){
        input = input.substring(0, i) + input.substring(i+1, input.length());
      }
    }
    input += '\0';
  }
}