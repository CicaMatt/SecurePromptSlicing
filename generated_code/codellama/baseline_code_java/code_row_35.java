import java.io.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.WebServlet;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

@WebServlet("/Login")
public class Login extends HttpServlet {

    private static final long serialVersionUID = 1L;

    public void init() throws ServletException {
        // do nothing.
    }

    public void destroy() {
        // do nothing.
    }

    public void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        
        String userName = request.getParameter("user_name");
        String password = request.getParameter("password");

        try {
            // Set database credentials and execute query
            Class.forName("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root", "password");
            Statement statement = conn.createStatement();
            ResultSet resultset = statement.executeQuery("SELECT * FROM users WHERE userName='"+userName+"' AND password='"+password+"';");
            
            // Check if username and password exist in database
            if(resultset.next()) {
                response.sendRedirect("/home_page");
            } else {
                response.sendRedirect("/login_page");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}