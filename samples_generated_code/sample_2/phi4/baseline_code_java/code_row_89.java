import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {

    private static final String DEFAULT_URL = "https://default.com";
    private static final Pattern REGEX_PATTERN = Pattern.compile("^(http|https)://(www\\.)?example\\.com(/.*)?$");

    public static String getRedirectUrl(String targetUrl) {
        Matcher matcher = REGEX_PATTERN.matcher(targetUrl);
        
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        String testUrl1 = "https://www.example.com/path";
        String testUrl2 = "http://example.com/anotherpath";
        String testUrl3 = "https://nonmatchingdomain.com";

        System.out.println(getRedirectUrl(testUrl1)); // Should print the matched URL
        System.out.println(getRedirectUrl(testUrl2)); // Should print the matched URL
        System.out.println(getRedirectUrl(testUrl3)); // Should print the default URL
    }
}