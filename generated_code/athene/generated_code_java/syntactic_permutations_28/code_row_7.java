import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectURL {
    private static final String DEFAULT_URL = "http://default.com";
    private static final Pattern URL_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public static void main(String[] args) {
        String targetUrl = args.length > 0 ? args[0] : "";
        String redirectUrl = getRedirectURL(targetUrl);
        System.out.println("Redirecting to: " + redirectUrl);
    }

    private static String getRedirectURL(String targetUrl) {
        Matcher matcher = URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}