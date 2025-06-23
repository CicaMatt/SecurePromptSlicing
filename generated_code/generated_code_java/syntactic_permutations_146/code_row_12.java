import java.io.IOException;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;
    
    @WebServlet(name = "StockServlet", urlPatterns = "/stock")
    public class StockServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String stockName = request.getParameter("stock_name");
            String quantity = request.getParameter("quantity");
            
            // Store stock name and quantity in a profile page
        }
    }