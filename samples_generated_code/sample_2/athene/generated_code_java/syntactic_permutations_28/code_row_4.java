import java.util.regex.Pattern;

public class RedirectHandler {
    private final Pattern urlPattern;
    private final String redirectUrl;
    private final String defaultUrl;

    public RedirectHandler(String pattern, String redirectUrl, String defaultUrl) {
        this.urlPattern = Pattern.compile(pattern);
        this.redirectUrl = redirectUrl;
        this.defaultUrl = defaultUrl;
    }

    public String getRedirectUrl(String targetUrl) {
        if (urlPattern.matcher(targetUrl).matches()) {
            return redirectUrl;
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler("^https://example\\.com/.*", "https://redirected.example.com/", "https://default.example.com/");
        String targetUrl = "https://example.com/path";
        System.out.println(handler.getRedirectUrl(targetUrl));
    }
}