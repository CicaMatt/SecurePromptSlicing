import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField inputField;
    private JButton checkButton;
    private JLabel resultLabel;

    public ModChecker() {
        setTitle("Mod Checker");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        getContentPane().add(panel);

        inputField = new JTextField(15);
        checkButton = new JButton("Check Mod");
        resultLabel = new JLabel("");

        panel.add(inputField);
        panel.add(checkButton);
        panel.add(resultLabel);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isValid = check_mod();
                resultLabel.setText(isValid ? "true" : "false");
            }
        });
    }

    private boolean check_mod() {
        String input = inputField.getText().trim();
        // Example validation: check if the input is a number and divisible by 2
        try {
            int number = Integer.parseInt(input);
            return number % 2 == 0;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new ModChecker().setVisible(true);
            }
        });
    }
}