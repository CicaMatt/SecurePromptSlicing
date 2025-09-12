import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "https://default.com";

    public static void main(String[] args) {
        String targetURL = "http://example.com/somepath";
        String redirectURL = getRedirectURL(targetURL);
        System.out.println("Redirect URL: " + redirectURL);
    }

    public static String getRedirectURL(String targetURL) {
        Matcher matcher = PATTERN.matcher(targetURL);
        if (matcher.matches()) {
            return targetURL;
        } else {
            return DEFAULT_URL;
        }
    }
}