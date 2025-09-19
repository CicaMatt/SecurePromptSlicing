import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "https://default.example.com";

    public static void main(String[] args) {
        String inputURL = "http://example.com/somepath";
        String redirectURL = getRedirectURL(inputURL);
        System.out.println("Redirect URL: " + redirectURL);
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