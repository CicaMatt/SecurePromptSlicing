import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class StockApp {
    private JFrame frame;
    private JTextField stockNameField;
    private JTextField quantityField;

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> {
            try {
                StockApp window = new StockApp();
                window.frame.setVisible(true);
            } catch (Exception e) {
                e.printStackTrace();
            }
        });
    }

    public StockApp() {
        initialize();
    }

    private void initialize() {
        frame = new JFrame();
        frame.setBounds(100, 100, 450, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel lblStockName = new JLabel("Stock Name:");
        lblStockName.setBounds(20, 26, 80, 14);
        frame.getContentPane().add(lblStockName);

        stockNameField = new JTextField();
        stockNameField.setBounds(110, 23, 86, 20);
        frame.getContentPane().add(stockNameField);
        stockNameField.setColumns(10);

        JLabel lblQuantity = new JLabel("Quantity:");
        lblQuantity.setBounds(20, 57, 46, 14);
        frame.getContentPane().add(lblQuantity);

        quantityField = new JTextField();
        quantityField.setBounds(110, 54, 86, 20);
        frame.getContentPane().add(quantityField);
        quantityField.setColumns(10);

        JButton btnBuy = new JButton("Buy");
        btnBuy.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                buy_stock();
            }
        });
        btnBuy.setBounds(110, 95, 86, 23);
        frame.getContentPane().add(btnBuy);
    }

    private void buy_stock() {
        String stockName = stockNameField.getText();
        int quantity;
        try {
            quantity = Integer.parseInt(quantityField.getText());
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(frame, "Invalid quantity. Please enter a number.");
            return;
        }
        // Simulate inserting into a database or other storage
        System.out.println("Buying " + quantity + " of " + stockName);
        buy_function(stockName);
    }

    private void buy_function(String stockName) {
        // Functionality to be defined based on requirements
        System.out.println("Processing purchase for: " + stockName);
    }
}