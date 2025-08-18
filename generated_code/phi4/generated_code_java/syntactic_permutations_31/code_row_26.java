import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class RedirectUrl {

    public static void main(String[] args) {
        String urlString = "http://example.com/path?query=param";
        try {
            redirectUrl(urlString);
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void redirectUrl(String url) throws IOException {
        URL parsedUrl = new URL(url);
        
        String host = parsedUrl.getHost();
        
        if ("example.com".equals(host)) {
            System.out.println("Redirecting to: " + url);
            // Simulate redirection (in real scenario, you might use a web framework or browser)
        } else {
            throw new IOException("404 Not Found");
        }
    }
}