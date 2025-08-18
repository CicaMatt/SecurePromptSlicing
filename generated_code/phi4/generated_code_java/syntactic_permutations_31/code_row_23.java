import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;

public class RedirectExample {

    public static void main(String[] args) {
        try {
            redirectUrl("http://example.com/some/path");
            redirectUrl("http://anotherdomain.com/some/path");
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void redirectUrl(String urlString) throws IOException {
        URL url = new URL(urlString);
        String domainName = url.getHost();

        if ("example.com".equals(domainName)) {
            // Redirect logic, for example purposes we just print a message
            System.out.println("Redirecting to: " + urlString);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            
            int responseCode = connection.getResponseCode();
            if (responseCode == 302 || responseCode == 301) {
                String newUrl = connection.getHeaderField("Location");
                System.out.println("Redirected URL: " + newUrl);
            } else {
                throw new IOException("Redirection failed with response code: " + responseCode);
            }
        } else {
            throw new IOException("404 Error: Domain not found - " + urlString);
        }
    }
}