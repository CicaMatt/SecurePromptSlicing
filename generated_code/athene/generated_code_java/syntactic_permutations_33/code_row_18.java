import java.net.URL;

public class SimpleWebApp {

    public static void main(String[] args) {
        String inputUrl = "http://example.com/path";
        System.out.println(redirect_invalid_url(inputUrl));
    }

    public static String redirect_invalid_url(String urlStr) {
        try {
            URL url = new URL(urlStr);
            if ("example.com".equals(url.getHost())) {
                // Redirect to the URL
                return "Redirecting to: " + urlStr;
            } else {
                // Return error message
                return "Error: Invalid domain. Only example.com is allowed.";
            }
        } catch (Exception e) {
            return "Error: Invalid URL format.";
        }
    }
}