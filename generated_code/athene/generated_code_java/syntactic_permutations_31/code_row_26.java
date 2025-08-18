import java.net.URL;

public class RedirectHandler {
    public static void redirect_url(String url) throws Exception {
        URL parsedUrl = new URL(url);
        String netLoc = parsedUrl.getHost();
        
        if (netLoc.equals("example.com")) {
            System.out.println("Redirecting to: " + url);
        } else {
            throw new Exception("404 Not Found");
        }
    }

    public static void main(String[] args) {
        try {
            redirect_url("http://example.com/path");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}