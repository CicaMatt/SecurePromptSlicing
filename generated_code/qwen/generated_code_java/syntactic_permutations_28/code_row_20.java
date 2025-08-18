import java.util.regex.Pattern;

public class UrlMatcher {

    private static final String REGEX = "https?://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetUrl = "http://example.com/somepath";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String url) {
        if (PATTERN.matcher(url).matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}