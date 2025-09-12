import java.net.*;
import java.io.*;

public class RedirectUrl {
    public static void main(String[] args) {
        try {
            String inputUrl = "http://example.com/some/path";
            redirectUrl(inputUrl);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws IOException {
        URL parsedUrl = new URL(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            System.out.println("Redirecting to: " + url);
            // Simulate a redirection, in real scenario you might use response.sendRedirect(url)
        } else {
            throw new FileNotFoundException("404 Not Found");
        }
    }
}