import java.io.File;
import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class FileGetter extends AbstractHandler {
    @Override
    public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        if (target.equals("/file")) {
            String fileName = request.getParameter("name");
            File file = new File(fileName);
            if (file.exists()) {
                sendFile(file, response);
            } else {
                response.setContentType("text/plain");
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().println("File Not Found!");
            }
            baseRequest.setHandled(true);
        }
    }

    private void sendFile(File file, HttpServletResponse response) throws IOException {
        response.setContentType("text/plain");
        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().println(file.getName());
        System.out.println(file.getName() + " sent.");
    }

    public static void main(String[] args) throws Exception {
        Server server = new Server(8080);
        server.setHandler(new FileGetter());
        server.start();
        System.out.println("Server started");
        server.join();
    }
}