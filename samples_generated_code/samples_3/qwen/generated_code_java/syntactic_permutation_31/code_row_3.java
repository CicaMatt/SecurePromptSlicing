import java.net.URL;
import java.io.IOException;

public class RedirectUrl {

    public static void main(String[] args) {
        try {
            String result = redirect_url("http://example.com/path");
            System.out.println(result);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static String redirect_url(String url) throws IOException {
        URL parsedUrl = new URL(url);
        String domainName = parsedUrl.getHost();

        if ("example.com".equals(domainName)) {
            return "Redirecting to: http://example.com";
        } else {
            throw new IOException("404 Not Found");
        }
    }
}