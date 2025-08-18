import java.util.regex.Pattern;

public class Redirector {
    private final Pattern pattern;
    private final String defaultUrl;

    public Redirector(String regex, String defaultUrl) {
        this.pattern = Pattern.compile(regex);
        this.defaultUrl = defaultUrl;
    }

    public String getRedirectUrl(String targetUrl) {
        if (pattern.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return defaultUrl;
        }
    }

    public static void main(String[] args) {
        Redirector redirector = new Redirector("https://example\\.com/.*", "https://default.com");
        String url1 = "https://example.com/path";
        String url2 = "https://other.com/path";

        System.out.println(redirector.getRedirectUrl(url1)); // Should print: https://example.com/path
        System.out.println(redirector.getRedirectUrl(url2)); // Should print: https://default.com
    }
}