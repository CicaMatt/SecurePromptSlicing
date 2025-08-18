import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern REGEX_PATTERN = Pattern.compile("^https?://example\\.com/.*");
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetUrl = "https://example.com/somepath";
        String redirectUrl = getRedirectUrl(targetUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String url) {
        if (REGEX_PATTERN.matcher(url).matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}