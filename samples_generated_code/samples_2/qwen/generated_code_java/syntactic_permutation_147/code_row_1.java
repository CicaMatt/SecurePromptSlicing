import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "root", "password");

            String sql = "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);

            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                response.sendRedirect("stock_view.jsp");
            } else {
                response.getWriter().println("Error inserting data into database.");
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            response.getWriter().println("Database connection or query error: " + e.getMessage());
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class StockViewServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<html><body>");
        out.println("<h1>Stock Orders</h1>");

        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/stockdb", "root", "password");

            String sql = "SELECT * FROM orders";
            stmt = conn.createStatement();
            rs = stmt.executeQuery(sql);

            out.println("<table border='1'>");
            out.println("<tr><th>Stock Name</th><th>Quantity</th></tr>");
            while (rs.next()) {
                String stockName = rs.getString("stock_name");
                int quantity = rs.getInt("quantity");

                out.println("<tr><td>" + stockName + "</td><td>" + quantity + "</td></tr>");
            }
            out.println("</table>");
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            out.println("Database connection or query error: " + e.getMessage());
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }

        out.println("</body></html>");
    }
}