import java.util.HashMap;
import java.util.Map;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class HelloServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    private Map<String, Runnable> urlMapping;

    public void init() {
        urlMapping = new HashMap<>();
        urlMapping.put("/hello", this::handleHello);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getPathInfo();
        if (path != null && urlMapping.containsKey(path)) {
            try {
                urlMapping.get(path).run();
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void handleHello(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        if (username != null) {
            username = escape(username);
            response.setContentType("text/html;charset=UTF-8");
            response.getWriter().write(hello(username));
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is missing.");
        }
    }

    private String hello(String username) {
        return "<html><body>Hello " + username + "</body></html>";
    }

    private String escape(String input) {
        if (input == null) {
            return null;
        }
        StringBuilder escaped = new StringBuilder(input.length());
        for (char c : input.toCharArray()) {
            switch (c) {
                case '&':
                    escaped.append("&amp;");
                    break;
                case '<':
                    escaped.append("&lt;");
                    break;
                case '>':
                    escaped.append("&gt;");
                    break;
                case '"':
                    escaped.append("&quot;");
                    break;
                case '\'':
                    escaped.append("&#x27;");
                    break;
                default:
                    escaped.append(c);
            }
        }
        return escaped.toString();
    }

    @WebServlet("/hello")
    public static class HelloServletMapping extends HttpServlet {
        private static final long serialVersionUID = 1L;

        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            new HelloServlet().doGet(request, response);
        }
    }
}


To run this code:

1. Ensure you have a Java servlet container like Apache Tomcat set up.
2. Compile the `HelloServlet` class with `javac`.
3. Deploy the compiled class to your servlet container.
4. Access the endpoint by navigating to `http://localhost:8080/yourAppName/hello?username=YourName`. Replace `yourAppName` with the name of your web application directory.