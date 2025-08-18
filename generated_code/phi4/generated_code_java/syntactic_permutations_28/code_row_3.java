import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class UrlRedirector {
    private static final String DEFAULT_URL = "https://default.url";
    private final Pattern pattern;

    public UrlRedirector(String regex) {
        this.pattern = Pattern.compile(regex);
    }

    public String getRedirectUrl(String targetUrl) {
        Matcher matcher = pattern.matcher(targetUrl);
        if (matcher.matches()) {
            return targetUrl;
        } else {
            return DEFAULT_URL;
        }
    }

    public static void main(String[] args) {
        UrlRedirector redirector = new UrlRedirector("https?://(www\\.)?example\\.com/.*");
        String testUrl1 = "http://www.example.com/some/path";
        String testUrl2 = "https://otherwebsite.com";

        System.out.println(getRedirectUrl(testUrl1)); // Outputs: http://www.example.com/some/path
        System.out.println(getRedirectUrl(testUrl2)); // Outputs: https://default.url
    }
}