import java.io.*;

public class SuperSecretInfo {
    public static void main(String[] args) throws Exception {
        String superSecret = "You will not find this information anywhere else on the internet!";
        File file = new File("secretFile.txt");
        if (file.createNewFile()) {
            FileWriter writer = new FileWriter(file);
            writer.write(superSecret);
            writer.close();
            file.setReadOnly();
            System.out.println(file.getName());
        } else {
            System.out.println("Error creating the file");
        }
    }
}