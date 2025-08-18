import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Stock App");
        JPanel panel = new JPanel();

        JLabel stockNameLabel = new JLabel("Stock Name:");
        JTextField stockNameField = new JTextField(10);
        JLabel quantityLabel = new JLabel("Quantity:");
        JTextField quantityField = new JTextField(10);
        JButton buyButton = new JButton("Buy");

        panel.add(stockNameLabel);
        panel.add(stockNameField);
        panel.add(quantityLabel);
        panel.add(quantityField);
        panel.add(buyButton);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().add(panel);
        frame.pack();
        frame.setVisible(true);

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String stockName = stockNameField.getText();
                int quantity;
                try {
                    quantity = Integer.parseInt(quantityField.getText());
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter a valid quantity.", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                buy_stock(stockName, quantity);
            }
        });
    }

    public static void buy_stock(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "";
        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO purchases (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, stockName);
            stmt.setInt(2, quantity);
            stmt.executeUpdate();
            buy_function(stockName);
        } catch (SQLException ex) {
            JOptionPane.showMessageDialog(null, "Error: " + ex.getMessage(), "SQL Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static void buy_function(String stockName) {
        // Functionality to be implemented based on the stock name
        System.out.println("Buying stock: " + stockName);
    }
}