import java.io.IOException;
import java.net.URLDecoder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    private String escape(String input) {
        if (input == null) return "";
        StringBuilder buffer = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch(c) {
                case '<': buffer.append("&lt;"); break;
                case '>': buffer.append("&gt;"); break;
                case '&': buffer.append("&amp;"); break;
                case '"': buffer.append("&quot;"); break;
                default: buffer.append(c); break;
            }
        }
        return buffer.toString();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo == null || pathInfo.equals("/")) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String username = pathInfo.substring(1);
        username = URLDecoder.decode(username, "UTF-8");

        String result = hello(username);

        response.setContentType("text/html");
        response.getWriter().write(result);
    }

    private String hello(String username) {
        return "Hello, " + escape(username) + "!";
    }
}