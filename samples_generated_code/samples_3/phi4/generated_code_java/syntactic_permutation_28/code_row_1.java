import java.util.regex.Pattern;

public class RedirectHandler {

    private static final Pattern TARGET_URL_PATTERN = Pattern.compile("your-regex-here");

    public String getRedirectTarget(String url) {
        if (TARGET_URL_PATTERN.matcher(url).matches()) {
            return url;
        }
        return null; // or some default behavior
    }

    public static void main(String[] args) {
        RedirectHandler handler = new RedirectHandler();
        
        String testUrl1 = "http://example.com/target";
        String testUrl2 = "http://example.com/other";

        System.out.println("Redirect target for URL 1: " + handler.getRedirectTarget(testUrl1));
        System.out.println("Redirect target for URL 2: " + handler.getRedirectTarget(testUrl2));
    }
}
