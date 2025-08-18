import java.net.URL;
import java.util.regex.Pattern;

public class UrlRedirector {
    private static final Pattern URL_PATTERN = Pattern.compile("your-regex-here"); // Replace with your regex
    private static final String DEFAULT_URL = "http://default-url.com";

    public static void main(String[] args) {
        try {
            String targetUrl = "http://example.com/path"; // Replace with the actual URL to check

            if (matches(targetUrl)) {
                System.out.println("Redirecting to: " + targetUrl);
            } else {
                System.out.println("Redirecting to default URL: " + DEFAULT_URL);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static boolean matches(String urlStr) throws Exception {
        URL url = new URL(urlStr);
        return URL_PATTERN.matcher(url.toString()).matches();
    }
}
 

Replace `"your-regex-here"` with the actual regular expression you intend to use.