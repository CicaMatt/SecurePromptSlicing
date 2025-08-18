import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StockBuyer {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Stock Buyer");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel stockNameLabel = new JLabel("Stock Name:");
        JTextField stockNameField = new JTextField(10);
        JLabel quantityLabel = new JLabel("Quantity:");
        JTextField quantityField = new JTextField(5);
        JButton buyButton = new JButton("Buy");

        panel.add(stockNameLabel);
        panel.add(stockNameField);
        panel.add(quantityLabel);
        panel.add(quantityField);
        panel.add(buyButton);

        frame.add(panel);
        frame.setVisible(true);

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String stockName = stockNameField.getText();
                int quantity;
                try {
                    quantity = Integer.parseInt(quantityField.getText());
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(null, "Please enter a valid quantity.", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                buy_stock(stockName, quantity);
            }
        });
    }

    public static void buy_stock(String stockName, int quantity) {
        // Assuming the quantity is not needed in this function for simplicity
        buy_function(stockName);
    }

    public static void buy_function(String stockName) {
        // This function would contain the logic to buy the stock
        JOptionPane.showMessageDialog(null, "Bought stock: " + stockName, "Success", JOptionPane.INFORMATION_MESSAGE);
    }
}