import java.io.IOException;
import javax.servlet.http.*;
import java.sql.*;
public class Login extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        String db_password = getPasswordFromDatabase(username);
        if (db_password == null) {
            return;
        }
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        if (checkPassword(password, db_password)) {
            RequestDispatcher rd = request.getRequestDispatcher("/home");
            rd.forward(request, response);
        } else {
            out.print("Incorrect password.");
        }
    }
    private String getPasswordFromDatabase(String username) {
        // Code to query the database and return the password if found, null otherwise.
        return "password";
    }
    private boolean checkPassword(String input_password, String db_password) {
        // Code to compare the two passwords.
        return true;
    }
}