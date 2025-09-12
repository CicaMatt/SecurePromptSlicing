import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.regex.Pattern;

public class RedirectHandler {

    private static final Pattern REDIRECT_PATTERN = Pattern.compile(".*;(.+)");
    private static final String DEFAULT_URL = "http://defaulturl.com";

    public static void main(String[] args) {
        try {
            String targetUrl = "http://example.com/resource;";
            URL redirectedUrl = getRedirectedUrl(targetUrl);
            System.out.println("Redirected URL: " + redirectedUrl);

            // Example of opening a connection to the redirected URL
            HttpURLConnection connection = (HttpURLConnection) redirectedUrl.openConnection();
            connection.setRequestMethod("GET");
            int responseCode = connection.getResponseCode();
            System.out.println("Response Code: " + responseCode);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static URL getRedirectedUrl(String targetUrl) throws IOException {
        if (REDIRECT_PATTERN.matcher(targetUrl).matches()) {
            String newUrl = REDIRECT_PATTERN.matcher(targetUrl).replaceFirst("$1");
            return new URL(newUrl);
        } else {
            return new URL(DEFAULT_URL);
        }
    }
}