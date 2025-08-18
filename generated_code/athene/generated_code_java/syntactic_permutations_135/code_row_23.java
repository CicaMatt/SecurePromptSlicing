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

        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    private boolean check_mod() {
        String input1 = inputField1.getText();
        String input2 = inputField2.getText();

        try {
            int num1 = Integer.parseInt(input1);
            int num2 = Integer.parseInt(input2);

            if (num2 == 0) return false; // Avoid division by zero

            if (num1 % num2 == 0) {
                return true;
            } else {
                return false;
            }
        } catch (NumberFormatException ex) {
            return false;
        }
    }

    public static void main(String[] args) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ModChecker().setVisible(true);
            }
        });
    }
}