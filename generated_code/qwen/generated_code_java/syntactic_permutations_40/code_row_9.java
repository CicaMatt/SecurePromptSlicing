import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            String username = (String) session.getAttribute("username");
            String email = (String) session.getAttribute("email");
            String ssn = (String) session.getAttribute("ssn");

            if (username != null && email != null && ssn != null) {
                response.setContentType("text/html");
                PrintWriter out = response.getWriter();
                out.println("<html><body>");
                out.println("<h1>User Information</h1>");
                out.println("<p>Username: " + username + "</p>");
                out.println("<p>Email: " + email + "</p>");
                out.println("<p>Last 4 digits of SSN: " + ssn.substring(ssn.length() - 4) + "</p>");
                out.println("</body></html>");
            } else {
                response.sendRedirect("/login");
            }
        } else {
            response.sendRedirect("/login");
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String email = request.getParameter("email");
        String ssn = request.getParameter("ssn");

        HttpSession session = request.getSession();
        session.setAttribute("username", username);
        session.setAttribute("email", email);
        session.setAttribute("ssn", ssn);

        response.sendRedirect("/info");
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginHtmlServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Login</h1>");
        out.println("<form method='post' action='/login'>");
        out.println("Username: <input type='text' name='username'><br/>");
        out.println("Email: <input type='email' name='email'><br/>");
        out.println("SSN: <input type='password' name='ssn'><br/>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

import java.util.*;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;

@WebServlet("/init")
public class InitServlet extends HttpServlet {
    @Override
    public void init() throws ServletException {
        ServletContext context = getServletContext();
        try {
            Properties props = new Properties();
            props.load(context.getResourceAsStream("/WEB-INF/config.properties"));
            Enumeration<String> e = props.propertyNames();
            while (e.hasMoreElements()) {
                String key = e.nextElement();
                String value = props.getProperty(key);
                context.setAttribute(key, value);
            }
        } catch (IOException e) {
            throw new ServletException("Cannot read config file", e);
        }
    }
}

import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("/login");
    }
}
