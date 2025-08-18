import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyer extends JFrame {
    private JTextField stockNameField;
    private JTextField quantityField;
    private JButton buyButton;

    public StockBuyer() {
        setTitle("Stock Buyer");
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
        panel.add(buyButton);

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String stockName = stockNameField.getText();
                int quantity;
                try {
                    quantity = Integer.parseInt(quantityField.getText());
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(null, "Please enter a valid quantity.");
                    return;
                }
                buy_stock(stockName, quantity);
            }
        });
    }

    private void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        insertIntoDatabase(stockName, quantity);
    }

    private void buy_function(String stockName) {
        // Logic to handle the buying of a stock
        System.out.println("Buying stock: " + stockName);
    }

    private void insertIntoDatabase(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockmarket";
        String user = "root";
        String password = "";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String query = "INSERT INTO transactions (stock_name, quantity) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(null, "Error inserting data into the database: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                StockBuyer frame = new StockBuyer();
                frame.setVisible(true);
            }
        });
    }
}