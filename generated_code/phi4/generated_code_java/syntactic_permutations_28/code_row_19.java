import java.util.regex.Pattern;

public class UrlRedirector {
    private static final String DEFAULT_URL = "https://www.defaulturl.com";
    private final Pattern pattern;
    private final String targetUrl;

    public UrlRedirector(String regex, String targetUrl) {
        this.pattern = Pattern.compile(regex);
        this.targetUrl = targetUrl;
    }

    public String getRedirectUrl() {
        if (pattern.matcher(targetUrl).matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        UrlRedirector redirector = new UrlRedirector("https://www.example.com/.*", "https://www.example.com/page");
        System.out.println(redirector.getRedirectUrl()); // Output: https://www.example.com/page

        UrlRedirector nonMatchingRedirector = new UrlRedirector("https://www.example.com/.*", "https://www.otherurl.com");
        System.out.println(nonMatchingRedirector.getRedirectUrl()); // Output: https://www.defaulturl.com
    }
}