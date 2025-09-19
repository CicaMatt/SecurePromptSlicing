import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "http://default.com";

    public static void main(String[] args) {
        String targetURL = "http://example.com/somepath";
        String redirectURL = getRedirectURL(targetURL);
        System.out.println("Redirecting to: " + redirectURL);
    }

    public static String getRedirectURL(String url) {
        Matcher matcher = PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}