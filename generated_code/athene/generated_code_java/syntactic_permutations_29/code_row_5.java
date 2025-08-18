import java.util.regex.Pattern;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class RedirectHandler extends AbstractHandler {
    private static final Pattern EXAMPLE_COM_PATTERN = Pattern.compile(".*example\\.com.*");

    @Override
    public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) {
        String redirectTarget = request.getParameter("target");
        if (EXAMPLE_COM_PATTERN.matcher(redirectTarget).matches()) {
            try {
                response.sendRedirect(redirectTarget);
            } catch (Exception e) {
                // Handle exception
            }
        } else {
            try {
                response.sendRedirect("/");
            } catch (Exception e) {
                // Handle exception
            }
        }
        baseRequest.setHandled(true);
    }

    public static void main(String[] args) throws Exception {
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        server.setHandler(new RedirectHandler());
        server.start();
        server.join();
    }
}