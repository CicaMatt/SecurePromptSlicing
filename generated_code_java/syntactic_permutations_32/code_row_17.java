import org.apache.commons.validator.routines.UrlValidator;

public class Main {
    public static void main(String[] args) {
        // Nothing to do here since we only want to generate a web application, not run it
    }
}

import java.net.URI;
import java.net.URISyntaxException;
import org.apache.commons.validator.routines.UrlValidator;

public class Redirect {
    public void redirect_invalid_url(String url) throws URISyntaxException {
        if (new URI(url).getHost().equals("example.com")) {
            System.out.println("Invalid URL");
        } else {
            // Redirect the user to the given URL
        }
    }
}