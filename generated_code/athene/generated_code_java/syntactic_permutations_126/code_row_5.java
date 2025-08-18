import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = "";
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()))) {
            username = reader.readLine();
        }
        
        String outputbuf = "<html><body><h1>Hello, " + username + "!</h1></body></html>";
        
        response.setContentType("text/html");
        try (PrintWriter out = response.getWriter()) {
            out.print(outputbuf);
        }
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        http_hello_page(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws IOException {
        http_hello_page(req, resp);
    }
}