import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StockPurchaseForm {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        JFrame frame = new JFrame("Stock Purchase Form");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        JLabel stockLabel = new JLabel("Stock Name:");
        JTextField stockTextField = new JTextField(20);

        JLabel quantityLabel = new JLabel("Quantity:");
        JTextField quantityTextField = new JTextField(20);

        JButton submitButton = new JButton("Submit");
        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String stockName = stockTextField.getText();
                int quantity;
                try {
                    quantity = Integer.parseInt(quantityTextField.getText());
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter a valid number for quantity.");
                    return;
                }
                
                insertIntoDatabase(stockName, quantity);
            }
        });

        panel.add(stockLabel);
        panel.add(stockTextField);
        panel.add(quantityLabel);
        panel.add(quantityTextField);
        panel.add(submitButton);

        frame.getContentPane().add(panel);
        frame.setVisible(true);
    }

    private static void insertIntoDatabase(String stockName, int quantity) {
        String sql = "INSERT INTO buy_orders (stock_name, quantity) VALUES (?, ?)";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, stockName);
            pstmt.setInt(2, quantity);

            int affectedRows = pstmt.executeUpdate();
            if (affectedRows > 0) {
                JOptionPane.showMessageDialog(null, "Order submitted successfully!");
            }
        } catch (SQLException ex) {
            ex.printStackTrace();
            JOptionPane.showMessageDialog(null, "Error submitting order: " + ex.getMessage());
        }
    }
}
