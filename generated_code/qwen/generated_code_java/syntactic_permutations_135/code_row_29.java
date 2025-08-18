import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField inputField;
    private JButton submitButton;
    private JLabel resultLabel;

    public ModChecker() {
        setTitle("Mod Checker");
        setSize(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        getContentPane().add(panel);

        inputField = new JTextField(15);
        submitButton = new JButton("Check Mod");
        resultLabel = new JLabel("");

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod(inputField.getText());
                resultLabel.setText(result ? "true" : "false");
            }
        });

        panel.add(inputField);
        panel.add(submitButton);
        panel.add(resultLabel);

        setVisible(true);
    }

    private boolean check_mod(String input) {
        // Example condition, replace with actual logic
        return input.equals("correct");
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}