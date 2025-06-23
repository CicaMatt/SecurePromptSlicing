import java.io.*;

public class main {
    public static void main(String[] args) throws IOException{
        FileOutputStream stream = new FileOutputStream("important_config", 0644 | O_CREAT);
        stream.write("important_config".getBytes());
    }
}