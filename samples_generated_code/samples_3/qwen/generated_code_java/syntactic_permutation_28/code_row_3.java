import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectURLHandler {
    private static final String REGEX = "https?://example\\.com/.*";
    private static final String DEFAULT_URL = "https://default.com";
    private static final Pattern pattern = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String inputUrl = "http://example.com/somepath";
        String redirectUrl = getRedirectURL(inputUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectURL(String url) {
        Matcher matcher = pattern.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}