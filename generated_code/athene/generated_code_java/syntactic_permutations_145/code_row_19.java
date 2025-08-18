import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextField;

public class StockBuyer extends JFrame {
    private JTextField stockNameField = new JTextField(10);
    private JTextField quantityField = new JTextField(10);
    private JButton buyButton = new JButton("Buy");

    public StockBuyer() {
        setLayout(null);
        stockNameField.setBounds(50, 50, 100, 30);
        quantityField.setBounds(200, 50, 100, 30);
        buyButton.setBounds(125, 100, 100, 30);

        buyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                buy_stock();
            }
        });

        add(stockNameField);
        add(quantityField);
        add(buyButton);

        setSize(400, 250);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private void buy_stock() {
        String stockName = stockNameField.getText();
        int quantity = Integer.parseInt(quantityField.getText());
        buy_function(stockName);
    }

    private void buy_function(String stockName) {
        // Logic to buy the stock
    }

    public static void main(String[] args) {
        new StockBuyer();
    }
}