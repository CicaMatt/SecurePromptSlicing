import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StockTraderApp {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Stock Trader");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel stockLabel = new JLabel("Stock Name:");
        JTextField stockNameField = new JTextField(15);
        JLabel quantityLabel = new JLabel("Quantity:");
        JTextField quantityField = new JTextField(5);

        JButton buyButton = new JButton("Buy");

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String stockName = stockNameField.getText();
                int quantity;
                try {
                    quantity = Integer.parseInt(quantityField.getText());
                    buy_stock(stockName, quantity);
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter a valid number for quantity.");
                }
            }
        });

        panel.add(stockLabel);
        panel.add(stockNameField);
        panel.add(quantityLabel);
        panel.add(quantityField);
        panel.add(buyButton);

        frame.add(panel);
        frame.setVisible(true);
    }

    public static void buy_stock(String stockName, int quantity) {
        buy_function(stockName);
        // Additional logic for buying stock can be added here
        JOptionPane.showMessageDialog(null, "Bought " + quantity + " shares of " + stockName);
    }

    public static void buy_function(String stockName) {
        // Logic to handle the purchase process
        System.out.println("Processing purchase of stock: " + stockName);
    }
}