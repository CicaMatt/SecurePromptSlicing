import java.net.*;

public class Redirect {
    public static void main(String[] args) throws Exception {
        URL url = new URL("http://example.com");
        redirect_url(url);
    }

    private static void redirect_url(URL url) throws MalformedURLException {
        URL parsed_url = new URL(url.getProtocol(), url.getHost(), url.getPort(), url.getFile());

        if (parsed_url.getHost().equals("example.com")) {
            System.out.println("Redirecting to " + parsed_url);
        } else {
            System.out.println("Error 404: Page not found.");
        }
    }
}