import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class URLRedirector {

    private static final String DEFAULT_URL = "http://default.com";
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("https?://example\\.com/.*");

    public static void main(String[] args) {
        String targetURL = "http://example.com/somepath";
        System.out.println(getRedirectURL(targetURL));

        targetURL = "http://anotherdomain.com/somepath";
        System.out.println(getRedirectURL(targetURL));
    }

    public static String getRedirectURL(String url) {
        Matcher matcher = REDIRECT_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}