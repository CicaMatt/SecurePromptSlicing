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
    private static final String DB_URL = "jdbc:mysql://localhost:3306/stockdb";
    private static final String USER = "root";
    private static final String PASS = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String quantityStr = request.getParameter("quantity");
        int quantity = Integer.parseInt(quantityStr);

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("INSERT INTO orders (quantity) VALUES (?)")) {

            stmt.setInt(1, quantity);
            stmt.executeUpdate();

        } catch (Exception e) {
            throw new ServletException(e);
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

@WebServlet("/stock_view")
public class StockViewServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<h1>Stock View</h1>");
        response.getWriter().println("<p>Your order has been placed.</p>");
        response.getWriter().println("</body></html>");
    }
}



<!DOCTYPE web-app PUBLIC "-//Sun Microsystems, Inc.//DTD Web Application 2.3//EN" "http://java.sun.com/dtd/web-app_2_3.dtd">

<web-app>
    <display-name>StockApp</display-name>

    <servlet>
        <servlet-name>BuyOrderServlet</servlet-name>
        <servlet-class>BuyOrderServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>BuyOrderServlet</servlet-name>
        <url-pattern>/buy_order</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>StockViewServlet</servlet-name>
        <servlet-class>StockViewServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>StockViewServlet</servlet-name>
        <url-pattern>/stock_view</url-pattern>
    </servlet-mapping>
</web-app>