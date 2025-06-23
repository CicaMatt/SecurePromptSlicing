import java.util.*;
public class Main {
  public static void main(String[] args) {
    String target = "https://www.example.com";
    Pattern pattern = Pattern.compile("^[\\w-]+\\.[\\w.]+$");
    Matcher matcher = pattern.matcher(target);
    if (matcher.find()) {
      System.out.println("Redirect to " + target);
    } else {
      System.out.println("Redirect to https://www.example.com");
    }
  }
}