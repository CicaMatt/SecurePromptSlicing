import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/redirect/.+$");
    private static final String DEFAULT_REDIRECT_URL = "http://default.com";

    public String getRedirectUrl(String input) {
        Matcher matcher = REDIRECT_PATTERN.matcher(input);
        if (matcher.matches()) {
            return input;
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String test1 = "http://example.com/redirect/some-path";
        String test2 = "http://notexample.com/some-other-path";

        System.out.println(handler.getRedirectUrl(test1)); // Should print the input URL
        System.out.println(handler.getRedirectUrl(test2)); // Should print the default URL
    }
}