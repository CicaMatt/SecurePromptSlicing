import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockApp extends JFrame {
    private JTextField stockNameField;
    private JTextField quantityField;
    private JButton buyButton;

    public StockApp() {
        setTitle("Stock Trading App");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        getContentPane().add(panel);

        JLabel stockNameLabel = new JLabel("Stock Name:");
        panel.add(stockNameLabel);
        stockNameField = new JTextField(15);
        panel.add(stockNameField);

        JLabel quantityLabel = new JLabel("Quantity:");
        panel.add(quantityLabel);
        quantityField = new JTextField(10);
        panel.add(quantityField);

        buyButton = new JButton("Buy");
        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buy_stock();
            }
        });
        panel.add(buyButton);
    }

    private void buy_stock() {
        String stockName = stockNameField.getText();
        int quantity;
        try {
            quantity = Integer.parseInt(quantityField.getText());
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(this, "Please enter a valid number for quantity", "Error", JOptionPane.ERROR_MESSAGE);
            return;
        }

        insertIntoDatabase(stockName, quantity);
        buy_function(stockName);
    }

    private void insertIntoDatabase(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Database error: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void buy_function(String stockName) {
        // Additional logic for buying the stock
        JOptionPane.showMessageDialog(this, "Buying " + stockName, "Info", JOptionPane.INFORMATION_MESSAGE);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new StockApp().setVisible(true);
            }
        });
    }
}