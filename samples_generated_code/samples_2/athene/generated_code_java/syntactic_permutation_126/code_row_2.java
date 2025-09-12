import java.io.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        String username = reader.readLine();

        StringBuilder outputbuf = new StringBuilder();
        outputbuf.append("<html><body>");
        outputbuf.append("<h1>Hello, ").append(username).append("!</h1>");
        outputbuf.append("</body></html>");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.print(outputbuf.toString());
        out.close();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        doPost(request, response);
    }
}