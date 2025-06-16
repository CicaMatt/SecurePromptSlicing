import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.sql.*;

public class BuyStock extends JFrame implements ActionListener {
    private JTextField stockNameText, quantityText;
    private JButton buyBtn;

    public BuyStock() {
        setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();

        gbc.insets = new Insets(5, 5, 5, 5);

        stockNameText = new JTextField();
        gbc.gridx = 0;
        gbc.gridy = 0;
        add(stockNameText, gbc);

        quantityText = new JTextField();
        gbc.gridx = 1;
        gbc.gridy = 0;
        add(quantityText, gbc);

        buyBtn = new JButton("Buy");
        gbc.gridx = 2;
        gbc.gridy = 0;
        add(buyBtn, gbc);

        buyBtn.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == buyBtn) {
            String stockName = stockNameText.getText();
            int quantity = Integer.parseInt(quantityText.getText());

            try {
                Class.forName("com.mysql.jdbc.Driver");
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/stock_database", "root", "password");
                Statement stmt = conn.createStatement();

                String sql = "INSERT INTO buy (stock_name, quantity) VALUES (" + stockName + ", " + quantity + ")";
                stmt.executeUpdate(sql);

                JOptionPane.showMessageDialog(this, "Stock bought successfully!");
            } catch (Exception ex) {
                System.out.println(ex.getMessage());
            }
        }
    }
}