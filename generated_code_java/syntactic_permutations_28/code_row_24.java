import java.util.regex.Matcher;
    import java.util.regex.Pattern;
    
    public class Redirect {
      private final Pattern pattern;
      private final String targetUrl;
      private final String replacementUrl;
      
      public Redirect(String regex, String targetUrl, String replacementUrl) {
        this.pattern = Pattern.compile(regex);
        this.targetUrl = targetUrl;
        this.replacementUrl = replacementUrl;
      }
      
      public boolean matches(String url) {
        Matcher matcher = pattern.matcher(url);
        return matcher.matches();
      }
      
      public String redirectUrl(String url) {
        return matches(url) ? targetUrl : replacementUrl;
      }
    }