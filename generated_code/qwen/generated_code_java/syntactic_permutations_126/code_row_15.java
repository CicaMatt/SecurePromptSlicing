import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = "server"; // The server's username
        StringBuilder outputbuf = new StringBuilder();
        
        outputbuf.append("<html><head><title>Hello Page</title></head>");
        outputbuf.append("<body><h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.print(outputbuf.toString());
        out.close();
    }
}