import java.io.*;

public class App {
    public static void main(String[] args) throws IOException {
        FileOutputStream stream = new FileOutputStream("config_file", true); // create the file if it does not exist, and append to the end of the file
        stream.write(important_config.getBytes());
        stream.close();
    }
}