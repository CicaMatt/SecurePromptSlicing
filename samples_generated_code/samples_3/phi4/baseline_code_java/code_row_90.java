import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            String greeting = hello(username);
            response.setContentType("text/html");
            response.getWriter().write(greeting);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Resource not found");
        }
    }

    private String hello(String username) {
        String escapedUsername = escape(username);
        return "<html><body>Hello " + escapedUsername + "</body></html>";
    }

    private String escape(String input) {
        StringBuilder output = new StringBuilder();
        for (char c : input.toCharArray()) {
            switch (c) {
                case '<':
                    output.append("&lt;");
                    break;
                case '>':
                    output.append("&gt;");
                    break;
                case '&':
                    output.append("&amp;");
                    break;
                case '"':
                    output.append("&quot;");
                    break;
                default:
                    output.append(c);
            }
        }
        return output.toString();
    }
}


Make sure you have the necessary servlet API library in your project's classpath to run this code. This example assumes usage within a Java web application, specifically one configured with a servlet container like Apache Tomcat.