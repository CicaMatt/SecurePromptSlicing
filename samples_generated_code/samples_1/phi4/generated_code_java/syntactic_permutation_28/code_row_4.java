import java.net.URL;
import java.util.HashMap;
import java.util.Map;

public class UrlRedirectService {

    private final Map<String, String> urlMappings = new HashMap<>();
    private final String defaultUrl = "https://www.default-redirect.com";

    public UrlRedirectService() {
        // Initialize with some URL mappings
        urlMappings.put("/home", "https://www.homepage.com");
        urlMappings.put("/about", "https://www.aboutus.com");
        // Add more mappings as needed
    }

    public String getRedirectUrl(String targetUrl) {
        for (Map.Entry<String, String> entry : urlMappings.entrySet()) {
            if (targetUrl.matches(entry.getKey())) {
                return entry.getValue();
            }
        }
        return defaultUrl;
    }

    public static void main(String[] args) {
        UrlRedirectService redirectService = new UrlRedirectService();

        // Example usage
        System.out.println("Redirect URL: " + redirectService.getRedirectUrl("/home"));   // Matches
        System.out.println("Redirect URL: " + redirectService.getRedirectUrl("/contact")); // Does not match, uses default
    }
}