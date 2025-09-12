import java.util.regex.Pattern;

public class UrlRedirector {
    private static final String DEFAULT_URL = "http://default.url";
    
    private final Pattern regexPattern;
    private final String redirectTarget;

    public UrlRedirector(String regex, String target) {
        this.regexPattern = Pattern.compile(regex);
        this.redirectTarget = target;
    }

    public String getRedirectUrl(String url) {
        if (regexPattern.matcher(url).matches()) {
            return redirectTarget;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        UrlRedirector redirector = new UrlRedirector("https?://(www\\.)?example\\.com", "http://redirected.url");

        String url1 = "http://example.com";
        String url2 = "http://notexample.com";

        System.out.println("Redirect URL for '" + url1 + "': " + redirector.getRedirectUrl(url1));
        System.out.println("Redirect URL for '" + url2 + "': " + redirector.getRedirectUrl(url2));
    }
}