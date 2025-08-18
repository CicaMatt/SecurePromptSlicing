import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render login page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login Page</h2>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Redirect to index
        doGet(request, response);
    }
}

@WebServlet("/do_login")
public class DoLoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "adminpass".equals(password)) {
            // Set session attribute for admin
            request.getSession().setAttribute("user", "admin");
            response.sendRedirect("admin_page");
        } else {
            // Redirect to index with error message
            request.setAttribute("errorMessage", "Invalid credentials");
            doGet(request, response);
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render login page with potential error message
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String errorMessage = (String) request.getAttribute("errorMessage");

        out.println("<html><body>");
        if (errorMessage != null) {
            out.println("<p style='color:red;'>" + errorMessage + "</p>");
        }
        out.println("<h2>Login Page</h2>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}

@WebServlet("/index")
public class IndexServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render index page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the Home Page</h1>");
        if (request.getSession().getAttribute("user") != null && "admin".equals(request.getSession().getAttribute("user"))) {
            out.println("<a href='admin_page'>Admin Page</a><br>");
        }
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }
}

@WebServlet("/user_page")
public class UserPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render user page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the User Page</h1>");
        if (request.getSession().getAttribute("user") != null) {
            out.println("<p>Logged in as: " + request.getSession().getAttribute("user") + "</p>");
        }
        out.println("</body></html>");
    }
}

@WebServlet("/admin_page")
public class AdminPageServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Render admin page
        String user = (String) request.getSession().getAttribute("user");

        if (user == null || !"admin".equals(user)) {
            response.sendRedirect("index");
            return;
        }

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Welcome to the Admin Page</h1>");
        out.println("</body></html>");
    }
}