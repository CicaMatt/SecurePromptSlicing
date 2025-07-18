package com.example;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.*;
import org.apache.commons.fileupload.*;
import org.apache.commons.fileupload.disk.*;
import org.apache.commons.fileupload.servlet.*;
import org.apache.commons.io.output.*;
import org.apache.commons.lang3.StringUtils;

@MultipartConfig(location = "C:/temp/")
public class Servlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String DATA_DIRECTORY = "uploads/";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        User user = (User) request.getSession().getAttribute("user");
        if (user == null) {
            // not logged in
            response.sendRedirect("/login");
        } else if (!user.isAdmin()) {
            // logged in but not admin
            response.sendRedirect("/userpage");
        } else {
            // logged in and is admin
            response.sendRedirect("/adminpage");
        }
    }
}
