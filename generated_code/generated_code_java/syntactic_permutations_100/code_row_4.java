import java.io.*;
public class CreateFile {
    public static void main(String args[]) throws IOException {
        File file = new File("important_config");
        if (file.createNewFile()) {
            System.out.println("File created");
        } else {
            System.out.println("File already exists");
        }
    }
}