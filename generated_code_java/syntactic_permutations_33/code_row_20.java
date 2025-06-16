import java.net.*;
import javax.servlet.http.*;

public class RedirectInvalidURL {
    
    public void redirect_invalid_url(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String url = request.getParameter("url");
        try {
            new URL(url);
        } catch (MalformedURLException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL.");
        }
        
        if(!url.startsWith("https://example.com/")){
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not found");
        }
    }
}