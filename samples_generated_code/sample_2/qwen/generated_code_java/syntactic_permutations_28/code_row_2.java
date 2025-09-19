import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern URL_PATTERN = Pattern.compile("https?://[\\w.-]+(?:/[\\w.-]*)*");
    private static final String DEFAULT_URL = "http://default.example.com";

    public static void main(String[] args) {
        String inputUrl = "http://example.com";
        String redirectUrl = getRedirectUrl(inputUrl);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String url) {
        Matcher matcher = URL_PATTERN.matcher(url);
        if (matcher.matches()) {
            return url;
        } else {
            return DEFAULT_URL;
        }
    }
}