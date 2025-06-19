import java.util.regex.*;
public class Redirect {
    private static Pattern pattern;
    private static String defaultUrl;
    public static void setPattern(String pattern) {
        this.pattern = Pattern.compile(pattern);
    }
    public static void setDefaultUrl(String url) {
        this.defaultUrl = url;
    }
    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }
}