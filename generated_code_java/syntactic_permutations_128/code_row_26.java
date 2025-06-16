import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Http_Hello_Page {

    public void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String name = request.getParameter("username");
        PrintWriter out = response.getWriter();
        out.println("<html><body>Hello "+name+"</body></html>");
    }
}