import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectUrlSelector {

    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://[\\w.-]+(?:\\/[\\w.-]*)*$");
    private static final String DEFAULT_URL = "http://default.example.com";

    public static void main(String[] args) {
        String inputUrl = "http://example.com/some/path";
        String redirectUrl = getRedirectUrl(inputUrl);
        System.out.println("Selected Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String inputUrl) {
        Matcher matcher = REDIRECT_PATTERN.matcher(inputUrl);
        if (matcher.matches()) {
            return inputUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}