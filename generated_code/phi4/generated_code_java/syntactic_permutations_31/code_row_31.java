import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

public class URLRedirector {

    public static void main(String[] args) {
        try {
            redirectUrl("http://example.com/some/path");
            redirectUrl("http://anotherdomain.com/some/path");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void redirectUrl(String url) throws IOException, URISyntaxException {
        URI parsedUri = new URI(url);
        String domainName = parsedUri.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
        } else {
            throw new IOException("404 Not Found");
        }
    }
}