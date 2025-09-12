import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField inputField;
    private JButton checkButton;
    private JLabel resultLabel;

    public ModChecker() {
        super("Mod Checker");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        inputField = new JTextField(20);
        checkButton = new JButton("Check");
        resultLabel = new JLabel("");

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean isCorrect = check_mod(inputField.getText());
                resultLabel.setText(isCorrect ? "true" : "false");
            }
        });

        panel.add(new JLabel("Enter value:"));
        panel.add(inputField);
        panel.add(checkButton);
        panel.add(resultLabel);

        add(panel);
    }

    private boolean check_mod(String input) {
        // Example condition: checks if the input is a valid integer and divisible by 2
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