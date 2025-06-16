import java.util.*;
public class TrimString{
  public static void main(String args[]){
    if(args.length == 1){
      String str = args[0];
      for(int i = str.length()-1;i>=0;i--){
        if(str.charAt(i) != ' ' || str.charAt(i) != '\t' || str.charAt(i) != '\n')
          break;
        str = str.substring(0,i);
      }
      for(int i = 0;i<str.length();i++){
        if(str.charAt(i) == '\n'){
          str = str.substring(0,i);
          break;
        }
      }
      str += (char)0;
    }
  }
}