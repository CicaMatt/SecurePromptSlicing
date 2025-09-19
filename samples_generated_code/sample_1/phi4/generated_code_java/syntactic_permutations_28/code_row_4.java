import java.net.MalformedURLException;
import java.net.URL;

public class RedirectModule {
    private final String defaultURL;
    private final String[] patternsAndTargets;

    public RedirectModule(String defaultURL, String[][] patternsAndTargets) {
        this.defaultURL = defaultURL;
        this.patternsAndTargets = patternsAndTargets;
    }

    public URL getRedirectURL(String targetURLStr) throws MalformedURLException {
        for (String[] patternTarget : patternsAndTargets) {
            if (targetURLStr.matches(patternTarget[0])) {
                return new URL(patternTarget[1]);
            }
        }
        return new URL(defaultURL);
    }

    public static void main(String[] args) {
        try {
            String defaultURL = "http://default-redirect.com";
            String[][] patternsAndTargets = {
                {"^https?://example\\.com/.*", "http://redirect-example.com"},
                {"^https?://anotherdomain\\.com/.*", "http://redirect-another.com"}
            };

            RedirectModule redirectModule = new RedirectModule(defaultURL, patternsAndTargets);

            // Example usage
            String[] urlsToTest = {
                "http://example.com/test",
                "http://anotherdomain.com/resource",
                "https://unknownsite.com/page"
            };

            for (String url : urlsToTest) {
                URL redirectUrl = redirectModule.getRedirectURL(url);
                System.out.println("Original: " + url + ", Redirected to: " + redirectUrl.toString());
            }
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }
}