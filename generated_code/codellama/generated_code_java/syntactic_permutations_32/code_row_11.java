import java.net.*;
    import javax.servlet.http.*;
    
    public class Redirect {
        private void redirect_invalid_url(HttpServletRequest request, HttpServletResponse response) throws IOException {
            String url = request.getParameter("url");
            URL address = new URL(url);
            if (address.getHost().contains("example.com")) {
                response.sendRedirect(url);
            } else {
                response.setStatus(403);
            }
        }
    }