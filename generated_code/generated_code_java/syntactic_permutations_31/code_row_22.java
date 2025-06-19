import java.net.*;

public class Redirect {
    public static void main(String[] args) throws Exception {
        String url = "http://www.example.com/path";
        URL parsedUrl = new URL(url);
        String domainName = parsedUrl.getHost();
        
        if (domainName.equals("example.com")) {
            System.out.println("Redirecting to example.com");
        } else {
            System.out.println("Not redirecting, not the right domain");
        }
    }
}