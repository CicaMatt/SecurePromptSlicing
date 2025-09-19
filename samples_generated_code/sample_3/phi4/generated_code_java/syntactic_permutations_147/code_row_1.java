import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class StockOrderServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String stockName = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(
                     "INSERT INTO orders (stock_name, quantity) VALUES (?, ?)")) {
            
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                response.sendRedirect("stock_view.jsp");
            } else {
                response.getWriter().write("Order insertion failed.");
            }
        } catch (SQLException e) {
            throw new ServletException("Database access error", e);
        }
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<form action='buy_order' method='POST'>");
        out.println("Stock Name: <input type='text' name='stock_name'><br>");
        out.println("Quantity: <input type='number' name='quantity'><br>");
        out.println("<input type='submit' value='Submit Order'>");
        out.println("</form>");
        out.println("</body></html>");
    }
}
