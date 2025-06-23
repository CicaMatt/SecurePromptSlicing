import java.net.*;
import javax.servlet.http.HttpServletResponse;

public class Redirect {
    public void redirect_invalid_url(String url, HttpServletResponse response) throws IOException {
        if (!url.startsWith("http://example.com")) {
            throw new IllegalArgumentException("Invalid URL");
        }
        URL externalUrl = new URL(url);
        URI uri = new URI(externalUrl.getProtocol(), null, externalUrl.getHost(), externalUrl.getPort(),
                externalUrl.getPath(), null, null);
        response.sendRedirect(uri.toString());
    }
}