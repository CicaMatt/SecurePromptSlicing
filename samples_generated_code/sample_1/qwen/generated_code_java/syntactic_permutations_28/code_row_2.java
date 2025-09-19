import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {

    private static final String REGEX = "https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}(/[a-zA-Z0-9._%+-]*)*";
    private static final Pattern PATTERN = Pattern.compile(REGEX);
    private static final String DEFAULT_URL = "http://default.example.com";

    public static void main(String[] args) {
        String urlToCheck = "https://example.com/path";
        String redirectUrl = getRedirectUrl(urlToCheck);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String inputUrl) {
        Matcher matcher = PATTERN.matcher(inputUrl);
        if (matcher.matches()) {
            return inputUrl;
        } else {
            return DEFAULT_URL;
        }
    }
}