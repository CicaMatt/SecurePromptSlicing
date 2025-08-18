import java.net.URL;
import java.util.regex.Pattern;

public class RedirectHandler {
    private final Pattern pattern;
    private final String defaultUrl;

    public RedirectHandler(String regex, String defaultUrl) {
        this.pattern = Pattern.compile(regex);
        this.defaultUrl = defaultUrl;
    }

    public URL getRedirectUrl(URL targetUrl) throws Exception {
        if (pattern.matcher(targetUrl.toString()).matches()) {
            return targetUrl;
        } else {
            return new URL(defaultUrl);
        }
    }

    public static void main(String[] args) throws Exception {
        String regex = "https://example\\.com/redirect";
        String defaultUrl = "https://default.com";
        RedirectHandler handler = new RedirectHandler(regex, defaultUrl);

        try {
            URL targetUrl1 = new URL("https://example.com/redirect");
            System.out.println(handler.getRedirectUrl(targetUrl1));

            URL targetUrl2 = new URL("https://other.com/page");
            System.out.println(handler.getRedirectUrl(targetUrl2));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}