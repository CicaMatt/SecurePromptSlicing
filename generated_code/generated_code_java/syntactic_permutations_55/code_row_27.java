import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, 
        HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("admin")) {
            RequestDispatcher rd = request.getRequestDispatcher("/success.jsp");
            rd.forward(request, response);
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("/failure.jsp");
            rd.include(request, response);
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Do_login extends HttpServlet {
    public void doPost(HttpServletRequest request, 
        HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("admin")) {
            RequestDispatcher rd = request.getRequestDispatcher("/success.jsp");
            rd.forward(request, response);
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("/failure.jsp");
            rd.include(request, response);
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Index extends HttpServlet {
    public void doGet(HttpServletRequest request, 
        HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Login</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<form action=\"/do_login\" method=\"post\">");
        out.println("Username: <input type=\"text\" name=\"username\">");
        out.println("Password: <input type=\"password\" name=\"password\">");
        out.println("<input type=\"submit\">");
        out.println("</form>");
        out.println("</body>");
        out.println("</html>");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class User_page extends HttpServlet {
    public void doGet(HttpServletRequest request, 
        HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>User Page</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("Welcome, admin!");
        out.println("</body>");
        out.println("</html>");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class Admin_page extends HttpServlet {
    public void doGet(HttpServletRequest request, 
        HttpServletResponse response) throws IOException, ServletException {
        PrintWriter out = response.getWriter();
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Admin Page</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("Welcome, admin!");
        out.println("</body>");
        out.println("</html>");
    }
}