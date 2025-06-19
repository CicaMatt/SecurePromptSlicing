import java.util.*;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1){
      System.out.println("Usage: please provide a string");
      return;
    } else if (!args[0].getClass().equals(String.class)){
      System.out.println("Invalid argument type");
      return;
    }
    String trimmed = args[0].trim();
    for (int i = 0; i < trimmed.length(); i++){
      if (Character.isWhitespace(trimmed.charAt(i))){
        System.out.println("Invalid string, contains whitespace");
        return;
      }
    }
    String nullTerminated = trimmed + "\0";
  }
}