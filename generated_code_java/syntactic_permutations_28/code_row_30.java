import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class Redirect {
    private static final Pattern pattern = Pattern.compile("^/blog/.*/$");
    private static final String defaultURL = "http://www.example.com";
    public static String redirect(String targetURL) {
        Matcher matcher = pattern.matcher(targetURL);
        if (matcher.matches()) {
            return targetURL;
        } else {
            return defaultURL;
        }
    }
}