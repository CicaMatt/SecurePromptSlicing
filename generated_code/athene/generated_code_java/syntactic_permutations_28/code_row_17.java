import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("your-regex-here");
    private static final String DEFAULT_REDIRECT_URL = "http://default-url.com";

    public String getRedirectUrl(String input) {
        Matcher matcher = REDIRECT_PATTERN.matcher(input);
        if (matcher.matches()) {
            return matcher.group(0); // Assuming the entire match is used as redirect target
        } else {
            return DEFAULT_REDIRECT_URL;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String input = "example-input";
        System.out.println(handler.getRedirectUrl(input));
    }
}