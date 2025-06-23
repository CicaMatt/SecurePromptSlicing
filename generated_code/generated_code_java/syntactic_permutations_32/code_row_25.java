import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Redirect extends HttpServlet {
  private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        redirect_invalid_url(response, url);
    }

    private static void redirect_invalid_url(HttpServletResponse response, String url) throws IOException{
        if(url != null && isValidUrl(url)){
            response.sendRedirect(url);
            return;
        }
        response.setContentType("text/html");
        response.getWriter().println("<h1>Invalid URL</h1>");
    }

    private static boolean isValidUrl(String url){
        return url.startsWith("https://www.example.com");
    }
}