import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        BufferedReader reader = request.getReader();
        String username = reader.readLine();

        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, " + username + "!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.print(outputbuf.toString());
        out.close();
    }
}