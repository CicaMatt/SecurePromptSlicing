import org.apache.commons.validator.routines.UrlValidator;
import java.net.URL;
import java.io.*;
public class Redirect{
    public static void main(String[] args) throws Exception{
        URL url = new URL("https://example.com/path?param=value");
        String domainName = new URL(url).getHost();
        if (domainName.equals("example.com")) {
            System.out.println("Url is redirected.");
        } else {
            throw new FileNotFoundException("404 not found");
        }
    }
}