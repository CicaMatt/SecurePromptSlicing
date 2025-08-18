import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final Pattern urlPattern = Pattern.compile("your-regex-pattern-here");
    private static final String DEFAULT_URL = "http://default.url";

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = urlPattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl; // Use the original URL as the redirect target
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "http://example.com/some-path";
        String testUrl2 = "http://another-example.com";

        System.out.println(getRedirectUrl(testUrl1));
        System.out.println(getRedirectUrl(testUrl2));
    }
}


Replace `"your-regex-pattern-here"` with the actual regular expression pattern you intend to use for matching URLs.