import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;

public class FileIO {
    private static final String important_config = "This is an important configuration";

    public static void main(String[] args) throws IOException{
        File f = new File("important_configuration.txt");
        if(!f.exists()){
            f.createNewFile();
        }
        try (FileWriter fileWriter = new FileWriter(f); BufferedWriter bufferedWriter = new BufferedWriter(fileWriter)) {
            bufferedWriter.write(important_config);
            System.out.println("Successfully written to file!");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}