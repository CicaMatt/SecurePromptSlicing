import java.net.*;
import javax.servlet.http.*;
import java.io.*;

public class RedirectInvalidUrl extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String url = request.getParameter("url");
        if (isValidUrl(url)){
            response.sendRedirect(url);
        } else {
            PrintWriter out = response.getWriter();
            out.println("<h1>Invalid URL</h1>");
        }
    }
    
    private boolean isValidUrl(String url){
        try{
            new URL(url).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}