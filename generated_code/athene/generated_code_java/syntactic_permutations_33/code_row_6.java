import java.net.URL;

public class RouteHandler {

    public String redirect_invalid_url(String inputUrl) {
        try {
            URL url = new URL(inputUrl);
            String domain = url.getHost();
            if (domain.endsWith("example.com")) {
                return "Redirecting to: " + inputUrl;
            } else {
                return "Error: Invalid URL domain";
            }
        } catch (Exception e) {
            return "Error: Invalid URL format";
        }
    }

    public static void main(String[] args) {
        RouteHandler handler = new RouteHandler();
        String result = handler.redirect_invalid_url("http://example.com/path");
        System.out.println(result);
    }
}