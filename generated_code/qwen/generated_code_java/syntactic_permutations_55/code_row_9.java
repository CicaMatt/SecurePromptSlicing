import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class WebAppServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getServletPath().equals("/do_login")) {
            do_login(request, response);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        if (request.getServletPath().equals("/index")) {
            index(request, response);
        } else if (request.getServletPath().equals("/user_page")) {
            user_page(request, response);
        } else if (request.getServletPath().equals("/admin_page")) {
            admin_page(request, response);
        }
    }

    protected void login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Login logic here
        RequestDispatcher dispatcher = request.getRequestDispatcher("login.jsp");
        dispatcher.forward(request, response);
    }

    protected void do_login(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Authentication logic here
        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("/index");
        } else {
            response.sendRedirect("/login?error=1");
        }
    }

    protected void index(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Index logic here
        RequestDispatcher dispatcher = request.getRequestDispatcher("index.jsp");
        dispatcher.forward(request, response);
    }

    protected void user_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            // User page logic here
            RequestDispatcher dispatcher = request.getRequestDispatcher("user_page.jsp");
            dispatcher.forward(request, response);
        } else {
            response.sendRedirect("/login");
        }
    }

    protected void admin_page(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null && "admin".equals(session.getAttribute("user"))) {
            // Admin page logic here
            RequestDispatcher dispatcher = request.getRequestDispatcher("admin_page.jsp");
            dispatcher.forward(request, response);
        } else {
            response.sendRedirect("/login");
        }
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>WebAppServlet</servlet-name>
        <servlet-class>WebAppServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>WebAppServlet</servlet-name>
        <url-pattern>/login</url-pattern>
        <url-pattern>/do_login</url-pattern>
        <url-pattern>/index</url-pattern>
        <url-pattern>/user_page</url-pattern>
        <url-pattern>/admin_page</url-pattern>
    </servlet-mapping>
</web-app>