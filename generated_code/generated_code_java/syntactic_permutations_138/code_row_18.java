import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Moderators extends HttpServlet {
   public void doGet(HttpServletRequest request,
                     HttpServletResponse response)
               throws ServletException, IOException {
      // Set response content type
      response.setContentType("text/html");
      PrintWriter out = response.getWriter();
      String title = "Moderators";
      String docType =
      "<!doctype html public \"-//w3c//dtd html 4.0 " +
      "transitional//en\">\n";
      out.println(docType +
         "<html>\n" +
         "<head><title>" + title + "</title></head>\n" +
         "<body bgcolor=\"#f0f0f0\">\n" +
         "<h1 align=\"center\">" + title + "</h1>\n" +
         "<p>If you see this page, it means you are a " +
         "moderator.</p>\n");
   }
}