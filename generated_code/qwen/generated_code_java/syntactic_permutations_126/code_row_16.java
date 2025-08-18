import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><head><title>Hello Page</title></head>");
        outputbuf.append("<body><h1>Hello, ");
        if (username != null && !username.isEmpty()) {
            outputbuf.append(username);
        } else {
            outputbuf.append("Guest");
        }
        outputbuf.append("!</h1></body></html>");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println(outputbuf.toString());
        out.close();
    }
}