package com.company;
import java.lang.*;
import javax.servlet.*;
public class PingDecorator implements RequestHandler {
    private String url;
    public void handleRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String output = ping();
        System.out.println("Pinging: " + output);
    }
}