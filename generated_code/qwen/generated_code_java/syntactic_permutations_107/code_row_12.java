import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class SecretFileCreator {
    public static void main(String[] args) {
        File secretFile = new File("secret.txt");
        try (FileWriter writer = new FileWriter(secretFile)) {
            writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file.");
            e.printStackTrace();
        }

        if (secretFile.setReadable(false, false) && secretFile.setWritable(false, false)) {
            try {
                StringBuilder content = new StringBuilder();
                int i;
                try (java.io.FileReader fr = new java.io.FileReader(secretFile)) {
                    while ((i = fr.read()) != -1) {
                        content.append((char) i);
                    }
                } catch (IOException e) {
                    System.out.println("An error occurred while reading the file.");
                    e.printStackTrace();
                }

                System.out.println(content.toString());
            } catch (SecurityException se) {
                System.out.println("Failed to read the file due to restrictive settings.");
            }
        } else {
            System.out.println("Failed to set restrictive permissions on the file.");
        }
    }
}