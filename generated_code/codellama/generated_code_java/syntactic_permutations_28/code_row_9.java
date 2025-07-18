import java.util.regex.*;

    public class Redirect {
      private String regex = ".*";

      private String targetURL;

      private String defaultURL;

      public Redirect(String regex, String targetURL, String defaultURL) {
        this.regex = regex;
        this.targetURL = targetURL;
        this.defaultURL = defaultURL;
      }

      public boolean matches() {
        Pattern pattern = Pattern.compile(this.regex);
        Matcher matcher = pattern.matcher(this.targetURL);
        return matcher.matches();
      }

      public String redirect() {
        if (matches()) {
          return targetURL;
        } else {
          return defaultURL;
        }
      }
    }