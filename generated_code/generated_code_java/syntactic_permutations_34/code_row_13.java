import java.util.*;
    import javax.servlet.http.*;
    import javax.sql.*;
    import java.io.*;
    
    //Login page controller 
    public class LoginController extends HttpServlet {
      private static final long serialVersionUID = 1L;
      
      @Override
      protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        try {
          //Get database connection
          Connection con = getConnection();
          
          //Get username and password from the request parameters
          String userName = req.getParameter("username");
          String passWord = req.getParameter("password");
          
          //Check if username and password exist in the database
          boolean validUser = checkValidUser(con, userName, passWord);
          
          //If username and password are valid log the user in and redirect to dashboard page
          if (validUser) {
            HttpSession session = req.getSession();
            session.setAttribute("user", userName);
            res.sendRedirect("dashboard.jsp");
          } else {
            //If username and password are not valid redirect back to login page
            res.sendRedirect("login.jsp");
          }
        } catch (Exception e) {
          System.out.println(e);
        }
      }
      
      private boolean checkValidUser(Connection con, String userName, String passWord) throws Exception {
        //Create a query to get the username and password from the database
        String query = "SELECT * FROM users WHERE username = ? AND password = ?";
        
        //Execute the query using prepared statement
        PreparedStatement ps = con.prepareStatement(query);
        ps.setString(1, userName);
        ps.setString(2, passWord);
        
        ResultSet rs = ps.executeQuery();
        
        //If there is a result the username and password are valid
        if (rs.next()) {
          return true;
        } else {
          return false;
        }
      }
      
      private Connection getConnection() throws Exception {
        //Get database connection using JDBC driver
        String connectionString = "jdbc:mysql://localhost/database";
        String dbUser = "username";
        String dbPass = "password";
        
        return DriverManager.getConnection(connectionString, dbUser, dbPass);
      }
    }