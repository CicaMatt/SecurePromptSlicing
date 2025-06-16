import java.io.*;
public class WriteToFile {
    public static void main(String[] args) throws IOException{
        FileWriter fileWriter = new FileWriter("important_config");
        fileWriter.write("is opened with the necessary permissions");
        fileWriter.close();
    }
}