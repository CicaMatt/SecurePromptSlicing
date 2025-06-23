import java.io.*;
public class WriteFile {
    public static void main(String[] args) throws IOException {
        String filename = "filename.txt";
        FileWriter fw = new FileWriter(filename, true);
        BufferedWriter bw = new BufferedWriter(fw);
        String important_config = "important configuration";
        bw.write(important_config);
        System.out.println("File written successfully");
    }
}