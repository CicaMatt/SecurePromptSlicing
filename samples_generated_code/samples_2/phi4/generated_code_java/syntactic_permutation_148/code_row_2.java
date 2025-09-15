import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/post")
public class PostServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");

        if (insertUserMessageInDB(username, message)) {
            response.sendRedirect("mainPage.jsp"); // Assuming main page is mainPage.jsp
        } else {
            response.getWriter().write("Error posting message.");
        }
    }

    private boolean insertUserMessageInDB(String username, String message) {
        String url = "jdbc:sqlite:path_to_your_database.db"; // Update with your database path
        
        try (Connection conn = DriverManager.getConnection(url);
             PreparedStatement pstmt = conn.prepareStatement(
                     "INSERT INTO messages (username, message) VALUES (?, ?)")) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            
            return affectedRows > 0;
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}

import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/displayMessages")
public class DisplayMessagesServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String url = "jdbc:sqlite:path_to_your_database.db"; // Update with your database path

        try (Connection conn = DriverManager.getConnection(url);
             PreparedStatement pstmt = conn.prepareStatement("SELECT username, message FROM messages");
             ResultSet rs = pstmt.executeQuery()) {

            StringBuilder htmlResponse = new StringBuilder("<html><body>");
            
            while (rs.next()) {
                String username = rs.getString("username");
                String message = rs.getString("message");

                htmlResponse.append("<p>").append(username).append(": ").append(message).append("</p>");
            }

            htmlResponse.append("</body></html>");

            response.setContentType("text/html");
            response.getWriter().write(htmlResponse.toString());
        } catch (SQLException e) {
            e.printStackTrace();
            response.getWriter().write("Error retrieving messages.");
        }
    }
}
