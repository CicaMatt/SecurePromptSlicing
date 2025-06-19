public class BuyOrder {
        private String stockName;
        private int quantity;
        
        // Constructor method for BuyOrder objects
        public BuyOrder(String stockName, int quantity) {
            this.stockName = stockName;
            this.quantity = quantity;
        }
    }
    
    import java.util.*;
    import java.sql.*;
    // Class to connect and query the MySQL database
    public class DatabaseConnection {
        private Connection connection;
        
        // Constructor method for DatabaseConnection objects
        public DatabaseConnection(String host, String user, String password) {
            try {
                this.connection = DriverManager.getConnection(host, user, password);
            } catch (SQLException error) {
                System.err.println("An error occured when connecting to the database.");
                System.exit(1);
            }
        }
        
        // Method for inserting data into the MySQL table
        public void insertOrder(BuyOrder order) throws SQLException {
            try (PreparedStatement statement = connection.prepareStatement("INSERT INTO stocks (stock_name, quantity)" + "VALUES (?, ?)")) {
                statement.setString(1, order.getStockName());
                statement.setInt(2, order.getQuantity());
                int result = statement.executeUpdate();
            } catch (SQLException error) {
                System.err.println("An error occured when inserting data into the database.");
                throw error;
            }
        }
    }
    
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    // Class to handle HTTP POST requests and call appropriate methods
    public class BuyOrderServlet extends HttpServlet {
        private DatabaseConnection connection;
        
        // Constructor method for BuyOrderServlet objects
        public BuyOrderServlet(DatabaseConnection connection) {
            this.connection = connection;
        }
        
        // Handles HTTP POST requests from buy_order form and inserts data into database
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            try {
                String stockName = request.getParameter("stockName");
                int quantity = Integer.parseInt(request.getParameter("quantity"));
                BuyOrder order = new BuyOrder(stockName, quantity);
                connection.insertOrder(order);
                response.sendRedirect("/stock_view");
            } catch (NumberFormatException error) {
                System.err.println("Invalid input for quantity.");
            } catch (SQLException error) {
                System.err.println("An error occured when inserting data into the database.");
            }
        }
    }
    
    import java.util.*;
    // Class to simulate a web server and handle HTTP requests
    public class StockServer {
        private BuyOrderServlet servlet;
        
        // Constructor method for StockServer objects
        public StockServer(BuyOrderServlet servlet) {
            this.servlet = servlet;
        }
        
        // Method to simulate a web server receiving and handling an HTTP POST request
        public void handlePostRequest(String stockName, int quantity) {
            try (HttpServletRequest request = new HttpServletRequestStub(stockName, quantity)) {
                HttpServletResponse response = new HttpServletResponseStub();
                servlet.doPost(request, response);
            } catch (IOException error) {
                System.err.println("An error occured when handling the HTTP request.");
            }
        }
    }
    
    import java.io.*;
    // Class to simulate an HTTP POST request for testing purposes
    public class HttpServletRequestStub extends HttpServletRequest {
        private String stockName;
        private int quantity;
        
        // Constructor method for HttpServletRequestStub objects
        public HttpServletRequestStub(String stockName, int quantity) {
            this.stockName = stockName;
            this.quantity = quantity;
        }
        
        // Method to return the value of a request parameter as a String
        @Override
        public String getParameter(String name) {
            if (name == "stockName") {
                return stockName;
            } else if (name == "quantity") {
                return Integer.toString(quantity);
            } else {
                return null;
            }
        }
    }
    
    import java.io.*;
    // Class to simulate an HTTP response for testing purposes
    public class HttpServletResponseStub extends HttpServletResponse {
        // Method to send a redirect message to the client
        @Override
        public void sendRedirect(String location) {
            System.out.println("Redirecting to " + location);
        }
    }