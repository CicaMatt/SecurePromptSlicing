import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileWriter myWriter = new FileWriter("filename.txt");
        myWriter.write("important_config");
        myWriter.close();
    }
}