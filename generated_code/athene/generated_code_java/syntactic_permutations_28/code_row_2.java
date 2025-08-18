import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("^https?://example\\.com/.*$");
    private static final String DEFAULT_URL = "http://default.example.com";

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        String targetUrl = "http://example.com/path";
        System.out.println(getRedirectUrl(targetUrl));
        
        targetUrl = "http://notexample.com/path";
        System.out.println(getRedirectUrl(targetUrl));
    }
}