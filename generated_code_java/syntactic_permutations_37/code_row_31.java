import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.sql.*;
@WebServlet(name = "Login", value = "/")
public class Login extends HttpServlet {
    // JDBC driver name and database URL
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    static final String DB_URL = "jdbc:mysql://localhost/";

    //  Database credentials
    static final String USER = "username";
    static final String PASS = "password";
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        //Connection with the database
        Connection conn = null;
        Statement stmt = null;
        String query = "SELECT username,password FROM login";
        ResultSet rs = null;
        
        try {
            //Register JDBC driver
            Class.forName("com.mysql.jdbc.Driver");
            
            //Open a connection
            System.out.println("Connecting to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
        
            //Execute a query
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            rs = stmt.executeQuery(query);
            
            String user=request.getParameter("username");
            String pass=request.getParameter("password");
            boolean flag=false;
            
            while (rs.next()) {
                if ((user.equals(rs.getString("username"))) && (pass.equals(rs.getString("password")))) {
                    response.sendRedirect("/success");
                    flag = true;
                    break;
                }
            }
            
            if (!flag) {
                response.sendRedirect("/cant_login");
            }
        } catch(SQLException se) {
            //Handle errors for JDBC
            se.printStackTrace();
            response.sendRedirect("/internal_server_error");
        } catch(Exception e) {
            //Handle errors for Class.forName
            e.printStackTrace();
            response.sendRedirect("/internal_server_error");
        } finally {
            //finally block used to close resources
            try{
                if (stmt != null)
                    conn.close();
            } catch(SQLException se){
            }// do nothing
            try {
                if (conn != null)
                    conn.close();
            } catch(SQLException se) {
                se.printStackTrace();
            }//end finally try
        } //end try
        out.close();
    }
}