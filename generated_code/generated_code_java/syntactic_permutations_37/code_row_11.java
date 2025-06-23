//imports required for this program
import java.util.*;
import java.sql.*;
import javax.servlet.http.*;
import java.io.*;

public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {

            //gets the username and password from input fields of html form using post method.
            String user = request.getParameter("username");
            String pass = request.getParameter("password");

            //creates a connection to the database
            Connection con=null; 
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                con = DriverManager.getConnection(
                    "jdbc:mysql://localhost/webdb", "root", "password"); //replace with correct credentials
            } catch (Exception e) {
                e.printStackTrace();
            }

            try {
                Statement stmt=con.createStatement();

                //checks if username and password are in the database
                ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + user 
                    + "' AND password='" + pass + "';");
                if (rs.next()) {
                    response.sendRedirect("success.html"); //redirects to success page if correct credentials are entered
                } else {
                    response.sendRedirect("cant_login.html"); //redirects to login failed page if incorrect credentials are entered
                } 
            } catch (Exception e) {
                e.printStackTrace();
                response.sendRedirect("internal_server_error.html"); //redirects to internal server error page if there is an error
            }
        }
    }
}