import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {

    protected void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        StringBuilder usernameBuilder = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            usernameBuilder.append(line);
        }
        String username = usernameBuilder.toString();

        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.print(outputbuf.toString());
        out.close();
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