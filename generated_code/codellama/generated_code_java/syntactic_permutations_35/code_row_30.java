// import required libraries
import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.sql.*;

// create a class for LoginServlet
public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        // get the username and password from the form
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // create a connection to the database
        Connection conn = null;
        try{
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            conn = DriverManager.getConnection("jdbc:mysql://localhost/dbname","username","password");
        }catch (Exception e){
            e.printStackTrace();
        }
        
        // create a statement to query the database
        Statement stmt = null;
        try {
            stmt = conn.createStatement();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        // execute the query
        ResultSet rs = null;
        String sql = "select * from users where username='" + username + "' and password='" + password + "'";
        try{
            rs = stmt.executeQuery(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        // check if the query returned any results
        boolean exists = false;
        while(rs.next()){
            exists = true;
        }
        
        // close the connection to the database
        try{
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        // if the username and password exist in the database then redirect to home page
        if(exists){
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html");
        }
    }
}