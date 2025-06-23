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

### Explanation:
The code uses Apache Commons FileUpload library to handle file uploads. It also uses the Servlet 3.0 API for multipart configuration. The `doGet` method first retrieves the user object from the session attribute "user". If the user is null, it means that the user has not logged in yet and redirects them to the login page. If the user is not an admin, it redirects them to the user page. Otherwise, it redirects them to the admin page.

### Links:
1. [Apache Commons FileUpload library](http://commons.apache.org/proper/commons-fileupload/)
2. [Servlet 3.0 API for multipart configuration](https://www.ibm.com/docs/en/was-liberty/base?topic=configuration-multiparts)