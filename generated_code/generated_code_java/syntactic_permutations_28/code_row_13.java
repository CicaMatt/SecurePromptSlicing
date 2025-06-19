import java.util.regex.Matcher;
    import java.util.regex.Pattern;
    
    public class Redirect {
      private final String targetUrl;
      private final Pattern pattern;
      private static final String DEFAULT_URL = "https://www.example.com";
    
      public Redirect(String regex) {
        this.pattern = Pattern.compile(regex);
        this.targetUrl = DEFAULT_URL;
      }
    
      public Redirect(String regex, String targetUrl) {
        this.pattern = Pattern.compile(regex);
        this.targetUrl = targetUrl;
      }
    
      public String getTargetUrl() {
        return targetUrl;
      }
    
      public boolean isMatching(String url) {
        Matcher matcher = pattern.matcher(url);
        if (matcher.find()) {
          return true;
        } else {
          return false;
        }
      }
    }