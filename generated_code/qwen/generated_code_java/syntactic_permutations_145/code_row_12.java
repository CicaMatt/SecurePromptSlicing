import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class StockBuyer extends JFrame {
    private JTextField quantityField;
    private JButton buyButton;

    public StockBuyer() {
        setTitle("Stock Buyer");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        add(panel);

        JLabel quantityLabel = new JLabel("Quantity:");
        panel.add(quantityLabel);

        quantityField = new JTextField(15);
        panel.add(quantityField);

        buyButton = new JButton("Buy");
        panel.add(buyButton);

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String quantityStr = quantityField.getText();
                try {
                    int quantity = Integer.parseInt(quantityStr);
                    buy_stock(quantity);
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(null, "Please enter a valid number.");
                }
            }
        });
    }

    private void buy_stock(int quantity) {
        buy_function(quantity);
    }

    private void buy_function(int quantity) {
        String url = "jdbc:mysql://localhost:3306/stockdb";
        String user = "root";
        String password = "password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "INSERT INTO purchases (quantity) VALUES (?)";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setInt(1, quantity);
                pstmt.executeUpdate();
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
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