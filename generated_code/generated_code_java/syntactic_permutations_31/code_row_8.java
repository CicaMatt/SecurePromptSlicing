java
import java.net.URL;
import java.nio.file.Paths;

public class Solution{
    public static void main(String[] args) {
        URL url = new URL("https://example.com/path/to/resource");
        URL parsed_url = Paths.get(url).getParent().toUri().toURL();
        String domainName = parsed_url.getHost();
        
        if (domainName == "example.com") {
            System.out.print("Redirected to example.com");
        } else {
            System.out.print("Error 404: Page not found");
        }
    }
}