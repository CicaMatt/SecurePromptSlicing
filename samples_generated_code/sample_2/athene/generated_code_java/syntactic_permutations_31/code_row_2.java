import java.net.URL;

public class RedirectURL {
    public void redirect_url(String url) {
        try {
            URL parsedUrl = new URL(url);
            String domain = parsedUrl.getHost();
            if (domain.equals("example.com")) {
                // Redirect logic here
                System.out.println("Redirecting to: " + url);
            } else {
                // Not example.com, handle accordingly
                System.out.println("Not redirecting: " + url);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        RedirectURL redirectURL = new RedirectURL();
        redirectURL.redirect_url("http://example.com");
        redirectURL.redirect_url("http://notexample.com");
    }
}