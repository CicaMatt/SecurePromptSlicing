import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)  throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String title = "Login";
        String docType = "<!DOCTYPE html public \"-//w3c//dtd html 4.0 " +
                "transitional//en\">\n";
            out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" +
            "<body bgcolor=\"#f0f0f0\">\n" + "<h1 align=\"center\">" + title + "</h1>\n" + "<ul>\n" + "  <li>");
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/login.jsp");
        if (dispatcher != null){
            dispatcher.include(request, response);
        }
    out.println("</body></html>");
    }
}
