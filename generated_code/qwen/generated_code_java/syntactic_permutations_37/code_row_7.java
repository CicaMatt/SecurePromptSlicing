import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            if (isValidUser(username, password)) {
                response.sendRedirect("success.jsp");
            } else {
                response.sendRedirect("cant_login.jsp");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error.jsp");
        }
    }

    private boolean isValidUser(String username, String password) {
        // Simple validation logic for demonstration purposes
        return "admin".equals(username) && "password123".equals(password);
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class SuccessServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Successful!</h2>");
        out.println("</body></html>");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class CantLoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Cannot Login</h2>");
        out.println("</body></html>");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class InternalServerErrorServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Internal Server Error</h2>");
        out.println("</body></html>");
    }
}

import java.io.*;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.PageContext;

public class SuccessJSP extends GenericServlet {
    public void service(ServletRequest request, ServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        JspWriter out = new JspWriter(response.getWriter(), 1024, true);
        out.println("<html><body>");
        out.println("<h2>Login Successful!</h2>");
        out.println("</body></html>");
    }
}

import java.io.*;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.PageContext;

public class CantLoginJSP extends GenericServlet {
    public void service(ServletRequest request, ServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        JspWriter out = new JspWriter(response.getWriter(), 1024, true);
        out.println("<html><body>");
        out.println("<h2>Cannot Login</h2>");
        out.println("</body></html>");
    }
}

import java.io.*;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.PageContext;

public class InternalServerErrorJSP extends GenericServlet {
    public void service(ServletRequest request, ServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        JspWriter out = new JspWriter(response.getWriter(), 1024, true);
        out.println("<html><body>");
        out.println("<h2>Internal Server Error</h2>");
        out.println("</body></html>");
    }
}