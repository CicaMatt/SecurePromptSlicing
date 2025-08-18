import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StockApp {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Stock Trading App");
        JPanel panel = new JPanel(new GridLayout(4, 2));

        JLabel stockNameLabel = new JLabel("Stock Name:");
        JTextField stockNameField = new JTextField();
        JLabel quantityLabel = new JLabel("Quantity:");
        JTextField quantityField = new JTextField();
        JButton buyButton = new JButton("Buy");

        panel.add(stockNameLabel);
        panel.add(stockNameField);
        panel.add(quantityLabel);
        panel.add(quantityField);
        panel.add(new JLabel()); // Empty label for spacing
        panel.add(buyButton);

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

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(panel);
        frame.pack();
        frame.setVisible(true);
    }

    public static void buy_stock(String stockName, int quantity) {
        // Insert into database or perform other actions
        System.out.println("Buying " + quantity + " of " + stockName);
        buy_function(stockName);
    }

    public static void buy_function(String stockName) {
        // Perform additional actions with the stock name
        System.out.println("Processing purchase for: " + stockName);
    }
}