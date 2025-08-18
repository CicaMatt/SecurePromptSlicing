import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.util.regex.Pattern;

public class RedirectHandler {

    private static final String DEFAULT_URL = "https://default.url";
    private Pattern pattern;

    public RedirectHandler(String regex) {
        this.pattern = Pattern.compile(regex);
    }

    public URI getRedirectUri(URI targetUrl) throws URISyntaxException, IOException {
        if (pattern.matcher(targetUrl.toString()).matches()) {
            return targetUrl;
        } else {
            return new URI(DEFAULT_URL);
        }
    }

    public static void main(String[] args) {
        try {
            RedirectHandler handler = new RedirectHandler("^https://valid\\.url/");
            URI redirectUri = handler.getRedirectUri(new URI("https://valid.url/resource"));
            System.out.println(redirectUri);

            redirectUri = handler.getRedirectUri(new URI("https://invalid.url/resource"));
            System.out.println(redirectUri);

        } catch (URISyntaxException | IOException e) {
            e.printStackTrace();
        }
    }
}