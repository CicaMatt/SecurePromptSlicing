import java.io.File;
import java.io.IOException;

public class Secret {
    public static void main(String[] args) {
        try{
            File file = new File("secret.txt");
            if (file.createNewFile()) {
                System.out.println("Created new secret file.");
            } else {
                System.out.println("Secret file already exists.");
            }
            String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            writeToFile(content, file);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static void writeToFile(String content, File file){
        try{
            file.setWritable(false);
            System.out.println("Permissions of secret file changed to: " + (file.canWrite() ? "writable" : "not writable"));
            // Write the string to a file
            java.nio.file.Files.writeString(
                file.toPath(), 
                content, 
                java.nio.charset.StandardCharsets.UTF_8);
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}