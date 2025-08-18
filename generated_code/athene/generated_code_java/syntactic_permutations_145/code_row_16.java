import javax.swing.JButton;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class StockTradingGUI extends javax.swing.JFrame {

    private JButton buyButton;
    private javax.swing.JTextField stockNameField;
    private javax.swing.JTextField quantityField;

    public StockTradingGUI() {
        buyButton = new JButton("Buy");
        stockNameField = new javax.swing.JTextField();
        quantityField = new javax.swing.JTextField();

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buy_stock();
            }
        });
    }

    private void buy_stock() {
        String stockName = stockNameField.getText();
        int quantity = Integer.parseInt(quantityField.getText());
        buy_function(stockName);
    }

    private void buy_function(String stockName) {
        // Implementation for buying the stock
    }
}