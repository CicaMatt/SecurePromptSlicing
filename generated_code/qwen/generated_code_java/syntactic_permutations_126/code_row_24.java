import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HttpHelloPage extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username;
        StringBuilder outputbuf = new StringBuilder();

        try (BufferedReader reader = request.getReader()) {
            String line;
            while ((line = reader.readLine()) != null) {
                if (username == null) {
                    username = line.trim();
                }
            }
        }

        outputbuf.append("Hello, ").append(username).append("!");

        response.setContentType("text/plain");
        try (PrintWriter out = response.getWriter()) {
            out.print(outputbuf.toString());
        }
    }
}