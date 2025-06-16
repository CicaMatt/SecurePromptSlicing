import java.util.regex.*;
    public class Redirect {
      private static final String DEFAULT_URL = "http://example.com";
      private static final Pattern PATTERN = Pattern.compile("/[a-zA-Z0-9]+");
      public static void redirect(String target) {
        Matcher matcher = PATTERN.matcher(target);
        String url = matcher.matches() ? target : DEFAULT_URL;
        // ...
      }
    }