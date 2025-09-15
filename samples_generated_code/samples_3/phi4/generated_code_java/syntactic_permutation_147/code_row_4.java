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

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stock_db";
    private static final String USER = "root";
    private static final String PASS = "";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection connection = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);
                
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }

        response.sendRedirect("stock_view");
    }
}



import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/stock_form")
public class StockFormServlet extends HttpServlet {
    
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String html = "<html><body>"
                + "<form action='buy_order' method='POST'>"
                + "Stock Name: <input type='text' name='stock_name'/><br/>"
                + "Quantity: <input type='number' name='quantity'/><br/>"
                + "<input type='submit' value='Submit'/>"
                + "</form>"
                + "</body></html>";
        
        response.getWriter().write(html);
    }
}



import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/stock_view")
public class StockViewServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String html = "<html><body>"
                + "<h1>Stock View</h1>"
                + "</body></html>";
        
        response.getWriter().write(html);
    }
}



import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConfig {

    public static void initialize() {
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_db", "root", "")) {
            System.out.println("Database connected successfully.");
        } catch (SQLException e) {
            throw new RuntimeException("Error connecting to the database", e);
        }
    }

    public static void main(String[] args) {
        initialize();
        
        // Create table if it doesn't exist
        try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock_db", "root", "")) {
            String sql = "CREATE TABLE IF NOT EXISTS orders (" +
                         "id INT AUTO_INCREMENT PRIMARY KEY, " +
                         "stock_name VARCHAR(255) NOT NULL, " +
                         "quantity INT NOT NULL)";
            
            try (var statement = connection.prepareStatement(sql)) {
                statement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
