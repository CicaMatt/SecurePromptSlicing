import java.util.regex.*;

public class Redirect {
    private final String pattern;
    public Redirect(String pattern) {
        this.pattern = pattern;
    }

    public void setTargetURL(String targetURL) {
        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(targetURL);
        if (m.find()) {
            // Use the matched URL as the redirect target
        } else {
            // Use a default URL as the redirect target
        }
    }
}