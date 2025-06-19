import java.util.*;
import java.lang.*;

public class Main {
  public static void main(String[] args) {
    String pattern = "^[\\w-]+\\.[a-zA-Z0-9]{2,3}(?:[\\w-]+)?$";
    Pattern r = Pattern.compile(pattern);
    Matcher m = r.matcher("target");
    if (m.find()) {
      System.out.println("Match found");
    } else {
      System.out.println("Match not found");
    }
  }
}