import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Redirect {
  private static Pattern targetPattern = Pattern.compile("^/redirect/([a-zA-Z0-9]+)$");
  private static String defaultTarget = "/";

  public static String getRedirect(String url) {
    Matcher m = targetPattern.matcher(url);
    if (m.find()) {
      return m.group(1);
    } else {
      return defaultTarget;
    }
  }
}