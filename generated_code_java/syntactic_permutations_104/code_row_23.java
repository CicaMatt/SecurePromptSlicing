import java.io.*;

public class FileOpen { 
    public static void main(String[] args) throws IOException {
        FileOutputStream file = new FileOutputStream("important_data.txt", true); // O_RDWR flag | O_CREAT flag
        file.write("important_config".getBytes());
        file.close();
    }
}