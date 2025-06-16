package main;
import java.io.*;
import java.net.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.catalina.core.ApplicationContext;
import org.apache.catalina.startup.Tomcat;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class MyWebApp extends AbstractHandler {
    public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        if (request.getMethod().equals("GET")) {
            String url = request.getParameter("url");
            if (!url.startsWith("http://example.com/")) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL.");
            } else {
                response.setContentType("text/html; charset=utf-8");
                response.sendRedirect(url);
            }
        }
    }
}