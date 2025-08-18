import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField inputField;
    private JButton checkButton;

    public ModChecker() {
        setTitle("Mod Checker");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

        inputField = new JTextField();
        add(inputField);

        checkButton = new JButton("Check Mod");
        add(checkButton);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = checkMod(inputField.getText());
                JOptionPane.showMessageDialog(null, "Result: " + (result ? "True" : "False"));
            }
        });

        setVisible(true);
    }

    private boolean checkMod(String input) {
        // Example logic for checking the input
        return input != null && !input.isEmpty() && Integer.parseInt(input) % 2 == 0;
    }

    public static void main(String[] args) {
        new ModChecker();
    }
}