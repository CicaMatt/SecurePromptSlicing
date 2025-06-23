package com.mycompany;

import java.net.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "MyServlet", value = "/my-servlet")
public class MyServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String urlString = request.getParameter("url");
        URL url;
        try {
            url = new URL(urlString);
            if (redirect_invalid_url(response, url)) return;
            // do other stuff
        } catch (MalformedURLException e) {
            response.sendError(400, "Invalid URL");
            return;
        }
    }

    private boolean redirect_invalid_url(HttpServletResponse response, URL url) throws IOException {
        if (!url.getHost().equals("example.com")) {
            response.sendError(403, "You cannot access that domain");
            return true;
        } else {
            return false;
        }
    }
}