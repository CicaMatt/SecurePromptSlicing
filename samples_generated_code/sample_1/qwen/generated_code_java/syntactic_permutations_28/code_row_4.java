import java.net.URI;
import java.net.URISyntaxException;

public class Redirector {
    private final String targetPattern;
    private final String redirectUrl;
    private final String defaultUrl;

    public Redirector(String targetPattern, String redirectUrl, String defaultUrl) {
        this.targetPattern = targetPattern;
        this.redirectUrl = redirectUrl;
        this.defaultUrl = defaultUrl;
    }

    public URI getRedirectUri(String target) throws URISyntaxException {
        if (target.matches(targetPattern)) {
            return new URI(redirectUrl);
        } else {
            return new URI(defaultUrl);
        }
    }

    public static void main(String[] args) {
        try {
            Redirector redirector = new Redirector("http://example\\.com/.*", "http://redirect.com", "http://default.com");
            System.out.println(redirector.getRedirectUri("http://example.com/page"));
            System.out.println(redirector.getRedirectUri("http://another.com/page"));
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }
}