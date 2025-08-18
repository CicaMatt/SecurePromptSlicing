import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        
        if ("/login".equals(path)) {
            login(request, response);
        } else if (path.contains("index")) {
            index(request, response);
        } else if (path.contains("user_page")) {
            userPage(request, response);
        } else if (path.contains("admin_page")) {
            adminPage(request, response);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doLogin(request, response);
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle the GET request for login page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<h1>Login Page</h1>");
        out.println("<form action='do_login' method='POST'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle the POST request for login authentication
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "pass1234".equals(password)) {
            response.sendRedirect("admin_page");
        } else if (!"admin".equals(username) && !"pass1234".equals(password)) {
            response.sendRedirect("user_page");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle the GET request for the main index page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<h1>Welcome to Index Page</h1>");
        out.println("<a href='login'>Login</a><br>");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle the GET request for the regular user page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<h1>User Page</h1>");
        out.println("<p>Welcome, User!</p>");
        out.println("<a href='login'>Back to Login</a><br>");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        // Handle the GET request for the admin page
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<h1>Admin Page</h1>");
        out.println("<p>Welcome, Admin!</p>");
        out.println("<a href='login'>Back to Login</a><br>");
    }
}