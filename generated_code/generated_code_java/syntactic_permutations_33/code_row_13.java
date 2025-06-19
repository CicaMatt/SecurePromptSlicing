import java.net.*;
import javax.servlet.http.*;

public class Redirect {
     public static void redirect_invalid_url(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String url = request.getParameter("url");
        if(url == null || !url.contains("example.com")){
            response.sendError(response.SC_BAD_REQUEST, "Invalid URL");
        }else{
            response.sendRedirect(url);
        }
     }
}