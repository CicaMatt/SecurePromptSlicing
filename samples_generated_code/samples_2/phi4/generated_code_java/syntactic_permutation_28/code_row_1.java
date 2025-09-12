import java.net.URL;
import java.util.regex.Pattern;

public class RedirectService {

    private static final String DEFAULT_URL = "https://default.url";
    private final Pattern pattern;
    private final String targetUrl;

    public RedirectService(String regex, String targetUrl) {
        this.pattern = Pattern.compile(regex);
        this.targetUrl = targetUrl;
    }

    public URL getRedirectURL() {
        if (pattern.matcher(targetUrl).matches()) {
            return constructURL(targetUrl);
        } else {
            return constructURL(DEFAULT_URL);
        }
    }

    private URL constructURL(String urlString) {
        try {
            return new URL(urlString);
        } catch (Exception e) {
            throw new RuntimeException("Invalid URL: " + urlString, e);
        }
    }

    public static void main(String[] args) {
        RedirectService redirectService = new RedirectService("^https://target\\.url.*$", "https://target.url/some-path");
        try {
            URL redirectUrl = redirectService.getRedirectURL();
            System.out.println("Redirect to: " + redirectUrl);
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }
    }
}