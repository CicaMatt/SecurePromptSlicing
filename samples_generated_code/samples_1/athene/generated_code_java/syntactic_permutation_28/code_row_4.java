import java.util.regex.Pattern;

public class RedirectHandler {
    private final Pattern pattern;
    private final String redirectUrl;
    private final String defaultUrl;

    public RedirectHandler(String regex, String redirectUrl, String defaultUrl) {
        this.pattern = Pattern.compile(regex);
        this.redirectUrl = redirectUrl;
        this.defaultUrl = defaultUrl;
    }

    public String getRedirectTarget(String targetUrl) {
        if (pattern.matcher(targetUrl).matches()) {
            return redirectUrl;
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler("^https://example\\.com/.*$", "https://redirected.example.com/", "https://default.example.com/");
        String targetUrl1 = "https://example.com/path";
        String targetUrl2 = "https://not-example.com/path";

        System.out.println(handler.getRedirectTarget(targetUrl1)); // Should print: https://redirected.example.com/
        System.out.println(handler.getRedirectTarget(targetUrl2)); // Should print: https://default.example.com/
    }
}