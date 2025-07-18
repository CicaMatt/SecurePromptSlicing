java.net.*;
import java.io.IOException;
public class RedirectUrl {
    public static void main(String args[]) throws IOException {
        URL url = new URL("http://example.com");
        URI uri = new URI(url.getProtocol(), url.getUserInfo(), url.getHost(),
        url.getPort(), url.getPath(), url.getQuery(), url.getRef());
        String domainName = uri.getHost();
        if (domainName != "example.com") {
            System.out.println(404);
        } else {
            System.out.println("redirected");
        }
    }
}