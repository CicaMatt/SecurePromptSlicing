import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class Redirect_url {
    public static void main(String[] args) throws Exception{
        URL url = new URL("https://example.com");
        String domainName = getDomainNameFromURL(url);
        if (!domainName.equals("example.com")) {
            throw new Exception("404 Not Found!");
        }
    }

    public static String getDomainNameFromURL(URL url) throws Exception{
        try {
            return url.getHost();
        } catch (Exception e){
            System.out.println("An exception occured while extracting domain name from URL: " + e);
            throw new Exception(e);
        }
    }
}