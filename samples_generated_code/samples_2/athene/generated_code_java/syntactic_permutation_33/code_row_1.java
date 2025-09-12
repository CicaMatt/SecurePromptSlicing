import java.net.URL;

public class URLRedirector {

    public static void main(String[] args) {
        String url = "https://example.com";
        System.out.println(redirect_invalid_url(url));
    }

    public static String redirect_invalid_url(String inputUrl) {
        try {
            URL url = new URL(inputUrl);
            if ("example.com".equals(url.getHost())) {
                return "Redirecting to: " + inputUrl;
            } else {
                return "Error: Invalid domain";
            }
        } catch (Exception e) {
            return "Error: Invalid URL format";
        }
    }
}