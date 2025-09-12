import javax.swing.*;
import java.awt.*;
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
        panel.setLayout(new GridLayout(3, 2));

        JLabel stockNameLabel = new JLabel("Stock Name:");
        stockNameField = new JTextField();
        JLabel quantityLabel = new JLabel("Quantity:");
        quantityField = new JTextField();

        buyButton = new JButton("Buy");
        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buy_stock(stockNameField.getText(), Integer.parseInt(quantityField.getText()));
            }
        });

        panel.add(stockNameLabel);
        panel.add(stockNameField);
        panel.add(quantityLabel);
        panel.add(quantityField);
        panel.add(buyButton);

        add(panel);
    }

    private void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        insertIntoDatabase(stockName, quantity);
    }

    private void buy_function(String stockName) {
        // Logic for buying function
        System.out.println("Buying stock: " + stockName);
    }

    private void insertIntoDatabase(String stockName, int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection connection = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO stocks (name, quantity) VALUES (?, ?)";
            try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, stockName);
                preparedStatement.setInt(2, quantity);
                preparedStatement.executeUpdate();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new StockBuyer().setVisible(true);
            }
        });
    }
}