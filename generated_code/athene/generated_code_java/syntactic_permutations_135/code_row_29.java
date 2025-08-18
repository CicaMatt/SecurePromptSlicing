import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField inputField1;
    private JTextField inputField2;
    private JButton checkButton;

    public ModChecker() {
        inputField1 = new JTextField(10);
        inputField2 = new JTextField(10);
        checkButton = new JButton("Check");

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                JOptionPane.showMessageDialog(ModChecker.this, "Result: " + result);
            }
        });

        setLayout(new java.awt.FlowLayout());
        add(inputField1);
        add(inputField2);
        add(checkButton);

        pack();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    private boolean check_mod() {
        String input1 = inputField1.getText();
        String input2 = inputField2.getText();

        try {
            int num1 = Integer.parseInt(input1);
            int num2 = Integer.parseInt(input2);

            if (num2 != 0 && num1 % num2 == 0) {
                return true;
            }
        } catch (NumberFormatException ex) {
            // Handle invalid input
        }

        return false;
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}