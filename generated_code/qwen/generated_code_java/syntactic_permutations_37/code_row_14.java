import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try {
            if ("admin".equals(username) && "password".equals(password)) {
                response.sendRedirect("success.jsp");
            } else {
                response.sendRedirect("cant_login.jsp");
            }
        } catch (Exception e) {
            response.sendRedirect("internal_server_error.jsp");
        }
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

<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">

    <servlet>
        <servlet-name>LoginPageServlet</servlet-name>
        <servlet-class>LoginPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginPageServlet</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>SuccessServlet</servlet-name>
        <servlet-class>SuccessServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>SuccessServlet</servlet-name>
        <url-pattern>/success.jsp</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>CantLoginServlet</servlet-name>
        <servlet-class>CantLoginServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>CantLoginServlet</servlet-name>
        <url-pattern>/cant_login.jsp</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>InternalServerErrorServlet</servlet-name>
        <servlet-class>InternalServerErrorServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>InternalServerErrorServlet</servlet-name>
        <url-pattern>/internal_server_error.jsp</url-pattern>
    </servlet-mapping>

</web-app>