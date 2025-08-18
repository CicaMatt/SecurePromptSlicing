import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final String DEFAULT_URL = "https://default.example.com";
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^/redirect/(.*)$");

    public String getRedirectUrl(String input) {
        Matcher matcher = REDIRECT_PATTERN.matcher(input);
        if (matcher.matches()) {
            return "https://target.example.com"; // Redirect target URL
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        System.out.println(handler.getRedirectUrl("/redirect/somepath")); // Should print: https://target.example.com
        System.out.println(handler.getRedirectUrl("/other/path"));     // Should print: https://default.example.com
    }
}