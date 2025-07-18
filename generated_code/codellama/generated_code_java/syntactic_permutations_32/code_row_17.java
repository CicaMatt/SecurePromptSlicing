import java.io.IOException;
    import java.net.URL;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    public class Main {
      private static String redirect_invalid_url(HttpServletRequest request) throws ServletException, IOException {
        URL url = new URL(request.getParameter("url"));
        if (url.getHost().endsWith("example.com")) {
          return null;
        } else {
          request.setAttribute("error", "Invalid URL");
          return "/WEB-INF/view/error.jsp";
        }
      }
    }