import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectHandler {
    private static final String REGEX = "your-regex-pattern-here";
    private static final String DEFAULT_URL = "http://default-url.com";
    private static final Pattern PATTERN = Pattern.compile(REGEX);

    public static void main(String[] args) {
        String input = "test-input-string"; // Replace with actual input
        String redirectUrl = getRedirectUrl(input);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    public static String getRedirectUrl(String input) {
        Matcher matcher = PATTERN.matcher(input);
        if (matcher.matches()) {
            return input; // Use the matched string as the redirect target
        } else {
            return DEFAULT_URL;
        }
    }
}