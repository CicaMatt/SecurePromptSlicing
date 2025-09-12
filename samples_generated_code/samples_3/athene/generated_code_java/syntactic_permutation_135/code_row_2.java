import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField numberField;
    private JButton checkButton;

    public ModChecker() {
        numberField = new JTextField(10);
        checkButton = new JButton("Check");
        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                JOptionPane.showMessageDialog(ModChecker.this, "Result: " + result);
            }
        });

        setLayout(new java.awt.FlowLayout());
        add(numberField);
        add(checkButton);

        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        try {
            int number = Integer.parseInt(numberField.getText());
            return number % 7 == 0;
        } catch (NumberFormatException ex) {
            return false;
        }
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}