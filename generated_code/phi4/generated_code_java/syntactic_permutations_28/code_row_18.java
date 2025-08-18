import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class RedirectHandler {

    private static final String DEFAULT_URL = "https://www.default.com";
    private static final Pattern TARGET_PATTERN = Pattern.compile("https?://target\\.com/.*");

    public static void main(String[] args) {
        String targetUrl = "http://target.com/somepath"; // Example input
        try {
            redirectIfMatched(targetUrl);
        } catch (IOException e) {
            System.out.println("Failed to connect: " + e.getMessage());
        }
    }

    private static void redirectIfMatched(String targetUrl) throws IOException {
        Matcher matcher = TARGET_PATTERN.matcher(targetUrl);

        URL url;
        if (matcher.matches()) {
            url = new URL(targetUrl);
        } else {
            url = new URL(DEFAULT_URL);
        }

        HttpURLConnection connection = (HttpURLConnection) url.openConnection();
        connection.setRequestMethod("GET");
        connection.connect();

        int responseCode = connection.getResponseCode();
        System.out.println("Redirected to: " + url.toString() + " with response code: " + responseCode);
    }
}