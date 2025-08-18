import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {

    private static final Pattern URL_PATTERN = Pattern.compile("https://example.com/target-regex");
    private static final String DEFAULT_URL = "https://default.example.com";

    public static void main(String[] args) {
        String targetUrl1 = "https://example.com/some-target-url";
        String targetUrl2 = "https://non-matching-domain.com/target-url";

        System.out.println(getRedirectUrl(targetUrl1)); // Should match the pattern
        System.out.println(getRedirectUrl(targetUrl2)); // Should not match, use default URL
    }

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = URL_PATTERN.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}