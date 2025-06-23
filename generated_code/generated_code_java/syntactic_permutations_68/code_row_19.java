import java.io.*;
import java.util.*;
import javax.swing.*;

public class ImageUploader {

    public static String upload_image() {
        String base64String = "";
        JFileChooser chooser = new JFileChooser();
        int returnVal = chooser.showOpenDialog(null);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            File file = chooser.getSelectedFile();
            try {
                byte[] bytes = Files.readAllBytes(file.toPath());
                base64String = Base64.encodeBase64String(bytes);
            } catch (IOException e) {
                System.out.println("Unable to read file: " + file.getAbsolutePath() + "\n" + e.getMessage());
            }
        }
        return base64String;
    }
}