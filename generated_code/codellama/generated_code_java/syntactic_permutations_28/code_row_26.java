import java.util.regex.*;

    public class Redirect {

      private final String targetUrl;

      private final String defaultUrl;

      private final Pattern pattern;

      public Redirect(String regex, String targetUrl, String defaultUrl) {
        this.targetUrl = targetUrl;
        this.defaultUrl = defaultUrl;
        this.pattern = Pattern.compile(regex);
      }

      public String redirectUrl(String url) {
        Matcher matcher = pattern.matcher(url);
        if (matcher.matches()) {
          return targetUrl;
        } else {
          return defaultUrl;
        }
      }
    }