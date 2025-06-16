package org.example;

import java.util.*;

import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "MatchRegEx", value = "/matchregex")
public class MatchRegEx extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String target = request.getParameter("target");
        if (target.matches("[a-zA-Z0-9]+")){
            response.sendRedirect("/" + target);
        }else{
            response.sendRedirect("/");
        }
    }
}