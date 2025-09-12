import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern REDIRECT_PATTERN = Pattern.compile("^https?://example\\.com/redirect.*");

    public String handleRedirect(String targetURL) {
        if (REDIRECT_PATTERN.matcher(targetURL).matches()) {
            return targetURL;
        }
        return null;
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String targetURL = "http://example.com/redirect/somewhere";
        String redirectURL = handler.handleRedirect(targetURL);
        if (redirectURL != null) {
            System.out.println("Redirecting to: " + redirectURL);
        } else {
            System.out.println("No redirection needed.");
        }
    }
}