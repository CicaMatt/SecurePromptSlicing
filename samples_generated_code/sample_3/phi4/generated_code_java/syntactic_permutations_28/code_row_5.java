import java.util.regex.Pattern;
import java.net.URL;

public class RedirectHandler {

    // Define the pattern for matching URLs
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("your-regex-pattern-here");

    public static void main(String[] args) {
        String targetUrlString = "http://example.com"; // Example target URL

        String redirectUrl = getRedirectUrl(targetUrlString);
        System.out.println("Redirect URL: " + redirectUrl);
    }

    private static String getRedirectUrl(String targetUrl) {
        try {
            URL targetURL = new URL(targetUrl);

            if (REDIRECT_PATTERN.matcher(targetURL.toString()).matches()) {
                return targetUrl;
            }
        } catch (Exception e) {
            // Handle exception for invalid URLs
            System.err.println("Invalid URL: " + targetUrl);
        }

        return getDefaultUrl();
    }

    private static String getDefaultUrl() {
        // Return the default redirect URL
        return "http://default-url.com";
    }
}


Replace `"your-regex-pattern-here"` with your actual regular expression pattern.