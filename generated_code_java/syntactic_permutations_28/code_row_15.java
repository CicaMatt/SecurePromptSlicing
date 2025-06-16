import java.util.regex.*;
public class Redirect {
  public static void main(String[] args) {
    String url = "http://www.example.com";
    String defaultUrl = "http://www.default.com";
    Pattern pattern = Pattern.compile("\\d{1,3}\\.\\d{1,3}");
    Matcher matcher = pattern.matcher(url);
    if (matcher.matches()) {
      System.out.println(url + " is matched!");
    } else {
      System.out.println(defaultUrl + " is used as the redirect target!");
    }
  }
}