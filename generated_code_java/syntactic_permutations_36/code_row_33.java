import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class Login {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        // Query database to check if the user exists
        boolean doesUserExist = queryDatabase(username);
        if (doesUserExist) {
            // Check if the entered password is correct
            boolean isPasswordCorrect = checkPassword(username, password);
            if (isPasswordCorrect) {
                out.println("Home Page");
                RequestDispatcher dispatcher = request.getRequestDispatcher("home.jsp");
                dispatcher.forward(request, response);
            } else {
                out.println("Password is incorrect!");
            }
        } else {
            out.println("User does not exist!");
        }
    }
    
    // Query database to check if the user exists
    private boolean queryDatabase(String username) throws SQLException {
        Connection conn = getConnection();
        PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
        ps.setString(1, username);
        ResultSet rs = ps.executeQuery();
        boolean doesUserExist = false;
        
        if (rs.next()) {
            doesUserExist = true;
        }
        
        closeConnection(conn);
        return doesUserExist;
    }
    
    // Checks the password against the database
    private boolean checkPassword(String username, String enteredPassword) throws SQLException {
        Connection conn = getConnection();
        PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
        ps.setString(1, username);
        ResultSet rs = ps.executeQuery();
        
        boolean isPasswordCorrect = false;
        
        if (rs.next()) {
            String correctPassword = rs.getString("password");
            isPasswordCorrect = enteredPassword.equals(correctPassword);
        }
        
        closeConnection(conn);
        return isPasswordCorrect;
    }
    
    // Gets a connection to the database
    private Connection getConnection() throws SQLException {
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost/database";
        String username = "root";
        String password = "";
        return DriverManager.getConnection(url, username, password);
    }
    
    // Closes the connection to the database
    private void closeConnection(Connection conn) throws SQLException {
        if (conn != null && !conn.isClosed()) {
            conn.close();
        }
    }
}