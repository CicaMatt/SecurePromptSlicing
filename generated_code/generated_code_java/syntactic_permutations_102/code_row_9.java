import java.io.*;

public class WriteToFile {
    public static void main(String[] args) throws IOException {
        open("important_config", "w");
        write("important_config", "Hello World!");
        close("important_config");
    }
}