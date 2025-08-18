import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField textField1;
    private JButton button1;

    public ModChecker() {
        textField1 = new JTextField(10);
        button1 = new JButton("Check");

        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                if (result) {
                    JOptionPane.showMessageDialog(ModChecker.this, "Correct");
                } else {
                    JOptionPane.showMessageDialog(ModChecker.this, "Incorrect");
                }
            }
        });

        setLayout(new java.awt.FlowLayout());
        add(textField1);
        add(button1);
        pack();
        setVisible(true);
    }

    private boolean check_mod() {
        String input = textField1.getText();
        // Assuming the correctness is determined by the input being a specific value, e.g., "correct"
        return "correct".equals(input);
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}