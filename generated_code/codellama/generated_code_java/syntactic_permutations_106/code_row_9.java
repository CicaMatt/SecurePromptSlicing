import java.io.*;

public class SecretInfo {
    public static void main(String[] args) throws IOException {
        String superSecretMessage = "I am a secret message, but not for long.";

        File file = new File("secret_message.txt");
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(superSecretMessage);
        }

        if (!file.setReadOnly()) {
            throw new IOException("Failed to set file to read-only.");
        }

        System.out.println(file.getAbsolutePath());
    }
}