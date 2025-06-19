import org.apache.commons.validator.routines.UrlValidator;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
public class RedirectUrl {
    public void redirect(String url, HttpServletResponse response) throws IOException {
        UrlValidator validator = new UrlValidator();
        if (validator.isValid(url)) {
            String domainName = parse_url(url).getNetworkLocation();
            if (domainName.equals("example.com")) {
                response.sendRedirect(url);
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
            }
        } else {
            throw new IOException("Invalid URL");
        }
    }
}