import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;

import org.eclipse.jetty.server.*;

public class Decorator {
    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        server.setHandler(new HelloHandler());
        server.start();
        server.join();
    }
}

class HelloHandler extends AbstractHandler {
    @Override
    public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Decode the path
        String path = URLDecoder.decode(request.getPathInfo(), "UTF-8");
        if (!path.startsWith("/hello/")) {
            return;
        }
        // Extract the username
        String username = path.substring(7);

        response.setContentType("text/html;charset=utf-8");
        baseRequest.setHandled(true);
        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().println("<h1>Hello " + escape(username) + "</h1>");
    }
}