import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username;
        try (BufferedReader reader = request.getReader()) {
            StringBuilder sb = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
            }
            username = sb.toString().trim();
        }

        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";

        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.println(outputbuf);
        }
    }
}