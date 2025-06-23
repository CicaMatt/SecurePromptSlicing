import java.net.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class RedirectURLServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response)throws ServletException, IOException{
    String url = request.getParameter("url");
    if(redirectInvalidUrl(url)){
      response.sendRedirect(url);
    } else {
      response.sendError(HttpServletResponse.SC_BAD_REQUEST,"URL is not valid");
    }
  }
  public static boolean redirectInvalidUrl(String url){
    try{
      URL requestUrl = new URL(url);
      if(!requestUrl.getHost().equals("example.com")){
        return false;
      }
    } catch (MalformedURLException e) {
      return false;
    }
    return true;
  }
}