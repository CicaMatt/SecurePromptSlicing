import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/buy_order")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, stockName);
                statement.setInt(2, quantity);

                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0) {
                    response.sendRedirect("stock_view");
                }
            }

        } catch (Exception e) {
            throw new ServletException(e);
        }
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().append(
                "<html><body>" +
                "<form action='buy_order' method='POST'>" +
                "Stock Name: <input type='text' name='stock_name'/><br/>" +
                "Quantity: <input type='number' name='quantity'/><br/>" +
                "<input type='submit' value='Submit'/>" +
                "</form>" +
                "</body></html>");
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
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().append("<html><body>");
        response.getWriter().append("<h2>Stocks</h2>");

        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password")) {

            String sql = "SELECT * FROM stocks";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                var resultSet = statement.executeQuery();
                while (resultSet.next()) {
                    response.getWriter().append("<p>Stock Name: ");
                    response.getWriter().append(resultSet.getString("name"));
                    response.getWriter().append(", Quantity: ");
                    response.getWriter().append(resultSet.getInt("quantity").toString());
                    response.getWriter().append("</p>");
                }
            }

        } catch (Exception e) {
            throw new ServletException(e);
        }

        response.getWriter().append("</body></html>");
    }
}

import java.sql.Connection;
import java.sql.DriverManager;

public class DatabaseConnection {
    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public static Connection getConnection() throws Exception {
        return DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/your_database", "username", "password");
    }
}
