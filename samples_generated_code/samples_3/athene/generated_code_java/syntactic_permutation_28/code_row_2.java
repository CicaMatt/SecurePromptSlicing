import java.util.regex.Pattern;
import java.net.URI;

public class RedirectHandler {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("^(https?://)?(www\\.)?example\\.com/.+$");

    public URI getRedirectURL(String targetURL) {
        if (TARGET_URL_PATTERN.matcher(targetURL).matches()) {
            return URI.create(targetURL);
        } else {
            return null;
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetURL = "http://example.com/somepath";
        URI redirectURL = handler.getRedirectURL(targetURL);
        if (redirectURL != null) {
            System.out.println("Redirecting to: " + redirectURL);
        } else {
            System.out.println("No redirection");
        }
    }
}