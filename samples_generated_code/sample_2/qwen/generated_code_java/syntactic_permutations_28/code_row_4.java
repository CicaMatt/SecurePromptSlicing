import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    private final URI targetURI;
    private final URI defaultURI;

    public URLRedirector(String targetURL, String defaultURL) throws URISyntaxException {
        this.targetURI = new URI(targetURL);
        this.defaultURI = new URI(defaultURL);
    }

    public URI getRedirectURI(URI requestURI) {
        if (requestURI.equals(targetURI)) {
            return targetURI;
        } else {
            return defaultURI;
        }
    }

    public static void main(String[] args) {
        try {
            URLRedirector redirector = new URLRedirector("http://example.com/target", "http://example.com/default");
            URI requestURI1 = new URI("http://example.com/target");
            URI requestURI2 = new URI("http://example.com/other");

            System.out.println("Redirect for target: " + redirector.getRedirectURI(requestURI1));
            System.out.println("Redirect for other: " + redirector.getRedirectURI(requestURI2));

        } catch (URISyntaxException e) {
            e.printStackTrace();
        }
    }
}