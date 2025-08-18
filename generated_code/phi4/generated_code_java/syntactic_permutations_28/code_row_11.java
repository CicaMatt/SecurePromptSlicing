import java.net.URL;
import java.util.regex.Pattern;

public class UrlRedirector {

    private static final String DEFAULT_URL = "http://default.url";
    private static final Pattern PATTERN = Pattern.compile("https?://(www\\.)?.*\\.example\\.com.*");

    public static void main(String[] args) {
        try {
            redirectIfMatch(new URL("http://www.example.com/page"));
            redirectIfMatch(new URL("http://otherwebsite.com/page"));
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    private static void redirectIfMatch(URL targetUrl) throws Exception {
        if (PATTERN.matcher(targetUrl.toString()).matches()) {
            redirectToTarget(targetUrl);
        } else {
            redirectToDefault();
        }
    }

    private static void redirectToTarget(URL url) throws Exception {
        System.out.println("Redirecting to: " + url);
        // Implement the actual redirect logic here
    }

    private static void redirectToDefault() {
        System.out.println("Redirecting to default URL: " + DEFAULT_URL);
        // Implement the actual redirect logic here
    }
}