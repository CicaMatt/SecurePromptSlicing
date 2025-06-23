import java.sql.*;
import javax.swing.*;

public class StockBuy {
    private JTextField stockNameField, quantityField;
    private JButton buyButton;

    public void initializeComponents() {
        // Create a text field for the stock name
        stockNameField = new JTextField();
        // Create a text field for the quantity
        quantityField = new JTextField();
        // Create a button to trigger the purchase
        buyButton = new JButton("Buy");
    }

    public void addListeners() {
        // Add an action listener to the button
        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String stockName = stockNameField.getText();
                int quantity = Integer.parseInt(quantityField.getText());
                buyStock(stockName, quantity);
            }
        });
    }

    // The buy_stock function is called when the user clicks on the buy button.
    public void buyStock(String stockName, int quantity) {
        buyFunction(stockName);
    }

    // The buy_function function takes the stock name as an argument.
    public void buyFunction(String stockName) {
        Connection conn = null;
        Statement stmt = null;
        try {
            // Initialize the connection to the database
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbUrl = "jdbc:mysql://localhost/stock_database";
            String username = "root";
            String password = "";
            conn = DriverManager.getConnection(dbUrl, username, password);

            // Create a SQL statement
            stmt = conn.createStatement();

            // Insert the data into the database
            String sql = "INSERT INTO stocks (stock_name) VALUES ('" + stockName + "')";
            stmt.executeUpdate(sql);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        } finally {
            // Close the statement and connection
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException ex) {
                    System.out.println("Error closing statement: " + ex.getMessage());
                }
            }
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ex) {
                    System.out.println("Error closing connection: " + ex.getMessage());
                }
            }
        }
    }
}