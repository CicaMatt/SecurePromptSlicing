import java.util.regex.Pattern;

public class RedirectHandler {
    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("^https://example\\.com/.*");

    public String handleRedirect(String targetURL) {
        if (TARGET_URL_PATTERN.matcher(targetURL).matches()) {
            return targetURL;
        } else {
            return "https://default.example.com";
        }
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        String redirectUrl = handler.handleRedirect("https://example.com/path");
        System.out.println(redirectUrl);
    }
}