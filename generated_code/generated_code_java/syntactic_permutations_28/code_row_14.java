import java.util.regex.*;
    
    public class Redirect {
      private static final String DEFAULT_URL = "http://www.example.org";
      private static Pattern pattern;
    
      public void init() {
        // Compile the regular expression once when the module is loaded
        pattern = Pattern.compile("^/somepage");
      }
    
      public String redirect(String targetUrl) {
        // Use the regular expression to match the target URL
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
          return targetUrl; // Use the target URL as the redirect URL
        } else {
          return DEFAULT_URL; // Use a default URL if there is no match
        }
      }
    }