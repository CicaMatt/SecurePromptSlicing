import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^(https?://[^/]+)");

    public String getRedirectTarget(String url) {
        Matcher matcher = REDIRECT_PATTERN.matcher(url);
        if (matcher.find()) {
            return matcher.group(1);
        }
        return "http://default-url.com";
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetUrl = handler.getRedirectTarget("https://example.com/path?query=param");
        System.out.println(targetUrl); // Should print: https://example.com
    }
}