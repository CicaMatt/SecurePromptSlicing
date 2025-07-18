java
import java.net.*;
public class Redirect {
    public static void main(String[] args) throws Exception {
        URL url = new URL("https://example.com");
        URI uri = new URI(url.getProtocol(), url.getAuthority(), url.getPath(), url.getQuery(), null);
        String domainName = uri.getHost();
        if (domainName == "example.com") {
            System.out.println("Redirected successfully!");
        } else {
            System.err.println("404 Not Found");
        }
    }
}