import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception {
        File file = new File("secret.txt");
        if (file.createNewFile()) {
            System.out.println("File created: " + file.getName());
        } else {
            System.out.println("File already exists.");
        }
        String content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        FileWriter myWriter = new FileWriter(file);
        myWriter.write(content);
        myWriter.close();
    }
}