import java.net.URL;
import java.net.URISyntaxException;
import java.util.logging.Logger;

public class Redirect {

    public static void redirectUrl(String url) throws URISyntaxException {
        Logger logger = Logger.getGlobal();
        URL parsedUrl = new URL(url);
        String domainName = parsedUrl.getHost();

        if (domainName.equals("example.com")) {
            // redirect to example.com
            logger.info("Redirecting to example.com");
        } else {
            // return 404 error
            logger.severe("Resource not found");
        }
    }
}