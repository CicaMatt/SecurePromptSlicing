import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField modField;
    private JButton checkButton;
    private JLabel resultLabel;

    public ModChecker() {
        super("Mod Checker");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(null);

        modField = new JTextField();
        modField.setBounds(50, 20, 200, 30);
        add(modField);

        checkButton = new JButton("Check");
        checkButton.setBounds(100, 60, 100, 30);
        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                resultLabel.setText(result ? "Correct" : "Incorrect");
            }
        });
        add(checkButton);

        resultLabel = new JLabel("");
        resultLabel.setBounds(120, 100, 60, 30);
        add(resultLabel);
    }

    private boolean check_mod() {
        String input = modField.getText();
        // Example validation: Check if the input is "correct"
        return "correct".equals(input);
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