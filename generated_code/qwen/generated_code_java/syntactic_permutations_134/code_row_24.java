import java.io.IOException;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/username")
public class UsernameServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        if (username != null) {
            username = escape(username);
            String result = "Hello " + username;
            response.setContentType("text/html");
            response.setCharacterEncoding(StandardCharsets.UTF_8.name());
            response.getWriter().write(result);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is required");
        }
    }

    private static String escape(String input) {
        StringBuilder result = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    result.append("&lt;");
                    break;
                case '>':
                    result.append("&gt;");
                    break;
                case '&':
                    result.append("&amp;");
                    break;
                case '"':
                    result.append("&quot;");
                    break;
                default:
                    result.append(c);
            }
        }
        return result.toString();
    }
}