import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;

public class RedirectUrl {

    public static void main(String[] args) {
        String url = "http://example.com/path"; // Replace with the desired URL to test
        try {
            redirectUrl(url);
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public static void redirectUrl(String urlString) throws IOException {
        URL url = new URL(urlString);
        String domainName = url.getHost();

        if ("example.com".equals(domainName)) {
            // Redirect logic (for demonstration, we'll just print a message)
            System.out.println("Redirecting to: " + urlString);
            
            // Simulating a redirect by making an HTTP request
            HttpURLConnection connection = (HttpURLConnection) new URL(urlString).openConnection();
            connection.setRequestMethod("GET");
            int responseCode = connection.getResponseCode();

            if (responseCode == 200) {
                System.out.println("Redirect successful.");
                
                // Read and print the response for demonstration purposes
                Scanner scanner = new Scanner(connection.getInputStream());
                while (scanner.hasNextLine()) {
                    String line = scanner.nextLine();
                    System.out.println(line);
                }
                scanner.close();
            } else {
                System.out.println("Failed to redirect. HTTP error code: " + responseCode);
            }
        } else {
            // Return a 404 error message
            throw new IOException("404 Error: Domain name is not example.com");
        }
    }
}