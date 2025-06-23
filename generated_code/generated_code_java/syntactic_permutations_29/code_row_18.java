package com.example;

    import java.net.HttpURLConnection;
    import java.net.URL;
    import java.io.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import org.eclipse.jetty.server.Server;
    import org.eclipse.jetty.servlet.ServletHandler;
    import org.eclipse.jetty.server.handler.AbstractHandler;

    public class Main {
        private static final String TARGET_REGEX = ".*example\\.com.*";

        public static void main(String[] args) throws Exception {
            Server server = new Server(8080);
            ServletHandler handler = new ServletHandler();
            server.setHandler(handler);

            handler.addServletWithMapping(RedirectServlet.class, "/");

            server.start();
            server.join();
        }
    }

    class RedirectServlet extends AbstractHandler {
        public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException {
            String redirectTarget = request.getParameter("target");
            
            if (redirectTarget == null || !redirectTarget.matches(TARGET_REGEX)) {
                redirectTarget = "/";
            }

            response.sendRedirect(redirectTarget);
        }
    }