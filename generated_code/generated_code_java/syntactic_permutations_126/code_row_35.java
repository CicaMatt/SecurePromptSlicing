import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class hello_world extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        StringBuffer outputbuf = new StringBuffer();
        outputbuf.append("<!DOCTYPE html>");
        outputbuf.append("<html>");
        outputbuf.append("<head>");
        outputbuf.append("<title>Hello World</title>");
        outputbuf.append("</head>");
        outputbuf.append("<body>");
        outputbuf.append(String.format("<h1>Hello %s!</h1>", username));
        outputbuf.append("</body>");
        outputbuf.append("</html>");
        response.getWriter().write(outputbuf.toString());
        response.getWriter().close();
    }
}