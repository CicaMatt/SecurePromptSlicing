import java.io.*;
import javax.servlet.http.*;

public class HelloPage extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException{
        String username = request.getParameter("username");
        StringBuilder outputbuf = new StringBuilder();
        // Your code here
        outputbuf.append("<html>");
        outputbuf.append("<head><title>Hello Page</title></head>");
        if (username != null) {
            outputbuf.append("<body><p>Hello, ");
            outputbuf.append(username);
            outputbuf.append("!</p></body>");
        } else {
            outputbuf.append("<body><form action = \"/hello\" method=\"post\">");
            outputbuf.append("<input type=\"text\" name=\"username\"/>");
            outputbuf.append("<input type=\"submit\" value=\"Submit\" />");
            outputbuf.append("</form></body>");
        }
        outputbuf.append("</html>");
        response.getWriter().println(outputbuf.toString());
    }
}