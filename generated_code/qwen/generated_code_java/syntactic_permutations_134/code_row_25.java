import java.io.IOException;
import java.net.URLDecoder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.length() > 1) {
            String username = URLDecoder.decode(pathInfo.substring(1), "UTF-8");
            String htmlSafeUsername = convertToHtmlSafe(username);
            String result = hello(htmlSafeUsername);
            response.setContentType("text/html");
            response.getWriter().write(result);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
        }
    }

    private String hello(String username) {
        return "Hello " + username;
    }

    private String convertToHtmlSafe(String input) {
        StringBuilder sb = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<': sb.append("&lt;"); break;
                case '>': sb.append("&gt;"); break;
                case '&': sb.append("&amp;"); break;
                case '"': sb.append("&quot;"); break;
                default: sb.append(c); break;
            }
        }
        return sb.toString();
    }
}